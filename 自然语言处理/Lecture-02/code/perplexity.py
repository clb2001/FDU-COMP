import nltk
from nltk.tokenize import word_tokenize
from nltk.lm import Laplace

# tokenize your training data
# training_data = "this is some training data"
# tokenized_data = [list(map(str.lower, word_tokenize(sent))) 
#                   for sent in nltk.sent_tokenize(training_data)]

# print(tokenized_data)

tokenized_data = ['this', 'is', 'some', 'training', 'data']
# train your bigram model
bigram_model = Laplace(2)
bigram_model.fit(tokenized_data)

# tokenize your test data
test_data = "this is some test data"
tokenized_test_data = list(map(str.lower, word_tokenize(test_data)))

# calculate the perplexity of the bigram model on the test data
perplexity = bigram_model.perplexity(tokenized_test_data)

print("Perplexity: ", perplexity)
