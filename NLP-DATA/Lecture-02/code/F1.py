import nltk
from sklearn.metrics import f1_score

# Load testing dataset and extract true labels and predicted labels
test_set = nltk.corpus.movie_reviews.test_set
true_labels = [label for (text, label) in test_set]
predicted_labels = [classifier.classify(text) for (text, label) in test_set]

# Calculate Micro-F1 score and Macro-F1 score
micro_f1 = f1_score(true_labels, predicted_labels, average='micro')
macro_f1 = f1_score(true_labels, predicted_labels, average='macro')

# Print the scores
print("Micro-F1 score:", micro_f1)
print("Macro-F1 score:", macro_f1)

