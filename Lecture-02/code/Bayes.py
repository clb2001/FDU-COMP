# import numpy as np

# class NaiveBayes:
    
#     def fit(self, X, y, alpha=1):
#         self.classes = np.unique(y)
#         self.n_classes = len(self.classes)
#         self.alpha = alpha
#         self.mean = np.zeros((self.n_classes, X.shape[1]))
#         self.var = np.zeros((self.n_classes, X.shape[1]))
#         self.prior = np.zeros(self.n_classes)
#         for i, c in enumerate(self.classes):
#             X_c = X[y == c]
#             self.mean[i] = X_c.mean(axis=0)
#             self.var[i] = X_c.var(axis=0)
#             self.prior[i] = X_c.shape[0] / X.shape[0]
    
#     def predict(self, X):
#         posteriors = []
#         for i, c in enumerate(self.classes):
#             prior = np.log(self.prior[i])
#             likelihood = np.sum(np.log(self._pdf(X, self.mean[i], self.var[i])), axis=1)
#             posterior = prior + likelihood
#             posteriors.append(posterior)
#         return self.classes[np.argmax(posteriors, axis=0)]
    
#     def _pdf(self, X, mean, var):
#         eps = 1e-6
#         pdf = (1 / np.sqrt(2 * np.pi * var + eps)) * np.exp(-0.5 * (X - mean)**2 / (var + eps))
#         return pdf + self.alpha

import nltk
from nltk.corpus import stopwords
from nltk.classify import NaiveBayesClassifier

def extract_features(text):
    text = text.lower()
    words = nltk.word_tokenize(text)
    # print(type(words))
    words = [word for word in words if word not in stopwords.words('english')]
    print(type(words))
    features = {}
    for word in words:
        features[word] = True
    return features

pos_data = [('This is a positive sentence.', 'positive'), ('I love this product.', 'positive'), ('Great job!', 'positive'), ('This is an awesome movie.', 'positive'), ('I highly recommend this book.', 'positive')]

neg_data = [('This is a negative sentence.', 'negative'), ('I hate this product.', 'negative'), ('Poor performance.', 'negative'), ('I did not like this movie.', 'negative'), ('I would not recommend this book.', 'negative')]

train_data = pos_data + neg_data

train_features = [(extract_features(text), label) for (text, label) in train_data]

classifier = NaiveBayesClassifier.train(train_features, estimator=nltk.LaplaceProbDist)

test_sentence = 'This product is great!'
test_features = extract_features(test_sentence)
print(classifier.classify(test_features))
