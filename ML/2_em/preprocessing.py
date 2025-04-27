from dataclasses import dataclass
from typing import Dict, List, Tuple
from collections import Counter

import numpy as np

import xml.etree.ElementTree as ET


@dataclass(frozen=True)
class SentencePair:
    """
    Contains lists of tokens (strings) for source and target sentence
    """
    source: List[str]
    target: List[str]


@dataclass(frozen=True)
class TokenizedSentencePair:
    """
    Contains arrays of token vocabulary indices (preferably np.int32) for source and target sentence
    """
    source_tokens: np.ndarray
    target_tokens: np.ndarray


@dataclass(frozen=True)
class LabeledAlignment:
    """
    Contains arrays of alignments (lists of tuples (source_pos, target_pos)) for a given sentence.
    Positions are numbered from 1.
    """
    sure: List[Tuple[int, int]]
    possible: List[Tuple[int, int]]


def extract_sentences(filename: str) -> Tuple[List[SentencePair], List[LabeledAlignment]]:
    """
    Given a file with tokenized parallel sentences and alignments in XML format, return a list of sentence pairs
    and alignments for each sentence.

    Args:
        filename: Name of the file containing XML markup for labeled alignments

    Returns:
        sentence_pairs: list of `SentencePair`s for each sentence in the file
        alignments: list of `LabeledAlignment`s corresponding to these sentences
    """
    with open(filename, "r", encoding="utf-8") as f:
        xml_content = f.read().replace("&", "&amp;")  

    root = ET.fromstring(xml_content)

    sentence_pairs = []
    alignments = []

    for part in root.findall("s"):
        english = part.find("english")
        cech = part.find("czech")
        english = english.text.split() if english is not None and english.text else []
        cech = cech.text.split() if cech is not None and cech.text else []

        sure_text = part.find("sure")
        possible_text = part.find("possible")
        sure_text = sure_text.text.strip() if sure_text is not None and sure_text.text else ""
        possible_text = possible_text.text.strip() if possible_text is not None and possible_text.text else ""

        sure = [tuple(map(int, pair.split("-"))) for pair in sure_text.split()] if sure_text else []
        possible = [tuple(map(int, pair.split("-"))) for pair in possible_text.split()] if possible_text else []

        sentence_pairs.append(SentencePair(english, cech))
        alignments.append(LabeledAlignment(sure, possible))

    return sentence_pairs, alignments


def get_token_to_index(sentence_pairs: List[SentencePair], freq_cutoff=None) -> Tuple[Dict[str, int], Dict[str, int]]:
    """
    Given a parallel corpus, create two dictionaries token->index for source and target language.

    Args:
        sentence_pairs: list of `SentencePair`s for token frequency estimation
        freq_cutoff: if not None, keep only freq_cutoff -- natural number -- most frequent tokens in each language

    Returns:
        source_dict: mapping of token to a unique number (from 0 to vocabulary size) for source language
        target_dict: mapping of token to a unique number (from 0 to vocabulary size) target language

    Tip: 
        Use cutting by freq_cutoff independently in src and target. Moreover in both cases of freq_cutoff (None or not None) - you may get a different size of the dictionary

    """
    source_tokens = [token for pair in sentence_pairs for token in pair.source]
    target_tokens = [token for pair in sentence_pairs for token in pair.target]

    source_counter = Counter(source_tokens)
    target_counter = Counter(target_tokens)

    if freq_cutoff is not None:
        source_counter = dict(source_counter.most_common(freq_cutoff))
        target_counter = dict(target_counter.most_common(freq_cutoff))

    source_dict = {token: idx for idx, token in enumerate(source_counter.keys())}
    target_dict = {token: idx for idx, token in enumerate(target_counter.keys())}

    return source_dict, target_dict


def tokenize_sents(sentence_pairs: List[SentencePair], source_dict, target_dict) -> List[TokenizedSentencePair]:
    """
    Given a parallel corpus and token_to_index for each language, transform each pair of sentences from lists
    of strings to arrays of integers. If either source or target sentence has no tokens that occur in corresponding
    token_to_index, do not include this pair in the result.

    Args:
        sentence_pairs: list of `SentencePair`s for transformation
        source_dict: mapping of token to a unique number for source language
        target_dict: mapping of token to a unique number for target language

    Returns:
        tokenized_sentence_pairs: sentences from sentence_pairs, tokenized using source_dict and target_dict
    """
    tokenized_sentence_pairs = []

    for pair in sentence_pairs:
        source_tokens = [source_dict[token] for token in pair.source if token in source_dict]
        target_tokens = [target_dict[token] for token in pair.target if token in target_dict]

        if source_tokens and target_tokens:
            tokenized_sentence_pairs.append(
                TokenizedSentencePair(
                    source_tokens=np.array(source_tokens, dtype=np.int32),
                    target_tokens=np.array(target_tokens, dtype=np.int32)
                )
            )

    return tokenized_sentence_pairs
