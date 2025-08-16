import re
from collections import defaultdict

def preprocess(text):
    # Convert to lowercase
    text = text.lower()
    
    # Remove non-alphabetic characters
    text = re.sub(r'[^a-z ]', '', text)
    
    # Tokenize
    tokens = text.split()
    
    return tokens

def add_one_smoothing(counts, vocabulary_size):
    # Add one to all counts
    smoothed_counts = defaultdict(int)
    for key in counts:
        smoothed_counts[key] = counts[key] + 1
    
    # Add vocabulary size to denominator
    smoothed_denominator = sum(smoothed_counts.values()) + vocabulary_size
    
    return smoothed_counts, smoothed_denominator

def build_unigram_model(tokens):
    # Count unigrams
    unigram_counts = defaultdict(int)
    for token in tokens:
        unigram_counts[token] += 1
    
    # Add-one smoothing
    vocabulary_size = len(unigram_counts.keys())
    smoothed_unigram_counts, smoothed_unigram_denominator = add_one_smoothing(unigram_counts, vocabulary_size)
    
    # Calculate probabilities
    unigram_probs = {}
    for token in smoothed_unigram_counts:
        unigram_probs[token] = smoothed_unigram_counts[token] / smoothed_unigram_denominator
    
    return unigram_probs

def build_bigram_model(tokens):
    # Count bigrams
    bigram_counts = defaultdict(int)
    for i in range(len(tokens) - 1):
        bigram = (tokens[i], tokens[i+1])
        bigram_counts[bigram] += 1
    
    # Add-one smoothing
    vocabulary_size = len(set(tokens))
    smoothed_bigram_counts, smoothed_bigram_denominator = add_one_smoothing(bigram_counts, vocabulary_size)
    
    # Calculate probabilities
    bigram_probs = {}
    for bigram in smoothed_bigram_counts:
        bigram_probs[bigram] = smoothed_bigram_counts[bigram] / smoothed_bigram_denominator
    
    return bigram_probs

def build_trigram_model(tokens):
    # Count trigrams
    trigram_counts = defaultdict(int)
    for i in range(len(tokens) - 2):
        trigram = (tokens[i], tokens[i+1], tokens[i+2])
        trigram_counts[trigram] += 1
    
    # Add-one smoothing
    vocabulary_size = len(set(tokens))
    smoothed_trigram_counts, smoothed_trigram_denominator = add_one_smoothing(trigram_counts, vocabulary_size)
    
    # Calculate probabilities
    trigram_probs = {}
    for trigram in smoothed_trigram_counts:
        trigram_probs[trigram] = smoothed_trigram_counts[trigram] / smoothed_trigram_denominator
    
    return trigram_probs

# Example usage
text = "The quick brown fox jumps over the lazy dog"
tokens = preprocess(text)

unigram_model = build_unigram_model(tokens)
print("Unigram model:")
print(unigram_model)

bigram_model = build_bigram_model(tokens)
print("Bigram model:")
print(bigram_model)

trigram_model = build_trigram_model(tokens)
print("Trigram model:")
print(trigram_model)
