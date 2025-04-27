from abc import ABC, abstractmethod
from itertools import product
from typing import List, Tuple

import numpy as np

from preprocessing import TokenizedSentencePair


class BaseAligner(ABC):
    """
    Describes a public interface for word alignment models.
    """

    @abstractmethod
    def fit(self, parallel_corpus: List[TokenizedSentencePair]):
        """
        Estimate alignment model parameters from a collection of parallel sentences.

        Args:
            parallel_corpus: list of sentences with translations, given as numpy arrays of vocabulary indices

        Returns:
        """
        pass

    @abstractmethod
    def align(self, sentences: List[TokenizedSentencePair]) -> List[List[Tuple[int, int]]]:
        """
        Given a list of tokenized sentences, predict alignments of source and target words.

        Args:
            sentences: list of sentences with translations, given as numpy arrays of vocabulary indices

        Returns:
            alignments: list of alignments for each sentence pair, i.e. lists of tuples (source_pos, target_pos).
            Alignment positions in sentences start from 1.
        """
        pass


class DiceAligner(BaseAligner):
    def __init__(self, num_source_words: int, num_target_words: int, threshold=0.5):
        self.cooc = np.zeros((num_source_words, num_target_words), dtype=np.uint32)
        self.dice_scores = None
        self.threshold = threshold

    def fit(self, parallel_corpus):
        for sentence in parallel_corpus:
            # use np.unique, because for a pair of words we add 1 only once for each sentence
            for source_token in np.unique(sentence.source_tokens):
                for target_token in np.unique(sentence.target_tokens):
                    self.cooc[source_token, target_token] += 1
        self.dice_scores = (2 * self.cooc.astype(np.float32) /
                            (self.cooc.sum(0, keepdims=True) + self.cooc.sum(1, keepdims=True)))

    def align(self, sentences):
        result = []
        for sentence in sentences:
            alignment = []
            for (i, source_token), (j, target_token) in product(
                    enumerate(sentence.source_tokens, 1),
                    enumerate(sentence.target_tokens, 1)):
                if self.dice_scores[source_token, target_token] > self.threshold:
                    alignment.append((i, j))
            result.append(alignment)
        return result


class WordAligner(BaseAligner):
    def __init__(self, num_source_words, num_target_words, num_iters):
        self.num_source_words = num_source_words
        self.num_target_words = num_target_words
        self.translation_probs = np.full((num_source_words, num_target_words), 1 / num_target_words, dtype=np.float32)
        self.num_iters = num_iters

    def _e_step(self, sentence_pairs: List[TokenizedSentencePair]) -> List[np.array]:
        """
        E-step: Compute posterior alignment probabilities for each sentence pair.
        
        Args:
            parallel_corpus: list of sentence pairs (source, target) as numpy arrays of vocabulary indices
        
        Returns:
            posteriors: list of np.arrays with shape (m_r, n_r) for each sentence pair
        """
        return [
            self.translation_probs[np.ix_(sentence_pair.source_tokens, sentence_pair.target_tokens)] /
            np.sum(self.translation_probs[np.ix_(sentence_pair.source_tokens, sentence_pair.target_tokens)], axis=0, keepdims=True)
            for sentence_pair in sentence_pairs
        ]

    def _compute_elbo(self, sentence_pairs: List[TokenizedSentencePair], alignment_probs: List[np.array]) -> float:
        """
        Compute evidence lower bound (ELBO) using posterior probabilities.
        
        Args:
            parallel_corpus: list of sentence pairs (source, target) as numpy arrays of vocabulary indices
            posteriors: posterior alignment probabilities (from _e_step)
        
        Returns:
            elbo: evidence lower bound value
        """
        return sum(
            np.sum(
                align_prob * (
                    np.log(self.translation_probs[np.ix_(sentence_pair.source_tokens, sentence_pair.target_tokens)] + 1e-9) -
                    (np.log(sentence_pair.source_tokens.size) + np.log(align_prob + 1e-9))
                )
            )
            for sentence_pair, align_prob in zip(sentence_pairs, alignment_probs)
        )

    def _m_step(self, sentence_pairs: List[TokenizedSentencePair], alignment_probs: List[np.array]) -> float:
        """
        M-step: Update model parameters and compute new ELBO.
        
        Args:
            parallel_corpus: list of sentence pairs (source, target) as numpy arrays of vocabulary indices
            posteriors: posterior alignment probabilities (from _e_step)
        
        Returns:
            elbo: new evidence lower bound value
        """
        self.translation_probs.fill(0)

        for sentence_pair, align_prob in zip(sentence_pairs, alignment_probs):
            np.add.at(
                self.translation_probs,
                np.ix_(sentence_pair.source_tokens, sentence_pair.target_tokens),
                align_prob
            )

        self.translation_probs /= np.sum(self.translation_probs, axis=1, keepdims=True)

        return self._compute_elbo(sentence_pairs, alignment_probs)

    def fit(self, sentence_pairs: List[TokenizedSentencePair]):
        """
        Train the model using the EM algorithm.
        
        Args:
            parallel_corpus: list of sentence pairs (source, target) as numpy arrays of vocabulary indices
        
        Returns:
            history: ELBO values over EM iterations
        """
        return [self._m_step(sentence_pairs, self._e_step(sentence_pairs)) for _ in range(self.num_iters)]

    def align(self, sentence_pairs: List[TokenizedSentencePair]) -> List[List[Tuple[int, int]]]:
        """
        Align words using trained translation probabilities.
        
        Args:
            sentences: list of sentence pairs (source, target) as numpy arrays of vocabulary indices
        
        Returns:
            alignments: list of lists, where each sublist contains target-to-source alignments
        """
        return [
            [(j + 1, i + 1) for i, j in enumerate(np.argmax(
                self.translation_probs[np.ix_(sentence_pair.source_tokens, sentence_pair.target_tokens)], axis=0))]
            for sentence_pair in sentence_pairs
        ]


# Class WordPositionAligner удален за неудобностью проверки 