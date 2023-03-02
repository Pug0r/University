# Dictionary to map letters to number pressed
word_to_seq_dict = dict.fromkeys(['a', 'b', 'c'], '2')
word_to_seq_dict.update(dict.fromkeys(['d', 'e', 'f'], '3'))
word_to_seq_dict.update(dict.fromkeys(['g', 'h', 'i'], '4'))
word_to_seq_dict.update(dict.fromkeys(['j', 'k', 'l'], '5'))
word_to_seq_dict.update(dict.fromkeys(['m', 'n', 'o'], '6'))
word_to_seq_dict.update(dict.fromkeys(['p', 'q', 'r', 's'], '7'))
word_to_seq_dict.update(dict.fromkeys(['t', 'u', 'v'], '8'))
word_to_seq_dict.update(dict.fromkeys(['w', 'x', 'y', 'z'], '9'))


def word_to_seq(word):
    """ Translates word to sequence of numbers """
    result = ''
    for letter in word:
        result += word_to_seq_dict[letter]
    return result


# Basically a list, with insertion and ability to modify order
class PrioritySeq:
    def __init__(self, data):
        if data == '':
            self.seq = []
        else:
            self.seq = [data]

    def insert(self, item):
        self.seq.append(item)

    def prior_up(self, item):
        if self.seq[0] == item:
            return 1
        for i, _ in enumerate(self.seq):
            if self.seq[i] == item:
                self.seq[i], self.seq[i - 1] = self.seq[i - 1], self.seq[i]
                return 1
        return -1

    def print(self):
        for elem in self.seq:
            print(elem)

    def get_word_list(self):
        return self.seq


class Trie:
    def __init__(self, data):
        self.two = None
        self.three = None
        self.four = None
        self.five = None
        self.six = None
        self.seven = None
        self.eight = None
        self.nine = None
        if data == '':
            self.data = PrioritySeq('')
        else:
            self.data = PrioritySeq(data)

    def insert(self, seq, word):
        match seq[0]:
            case '2':
                if len(seq) == 1:
                    if self.two is None:
                        self.two = Trie(word)
                    else:
                        self.two.data.insert(word)
                else:
                    if self.two is None:
                        self.two = Trie('')
                        self.two.insert(seq[1:], word)
                    else:
                        self.two.insert(seq[1:], word)

            case '3':
                if len(seq) == 1:
                    if self.three is None:
                        self.three = Trie(word)
                    else:
                        self.three.data.insert(word)
                else:
                    if self.three is None:
                        self.three = Trie('')
                        self.three.insert(seq[1:], word)
                    else:
                        self.three.insert(seq[1:], word)
            case '4':
                if len(seq) == 1:
                    if self.four is None:
                        self.four = Trie(word)
                    else:
                        self.four.data.insert(word)
                else:
                    if self.four is None:
                        self.four = Trie('')
                        self.four.insert(seq[1:], word)
                    else:
                        self.four.insert(seq[1:], word)
            case '5':
                if len(seq) == 1:
                    if self.five is None:
                        self.five = Trie(word)
                    else:
                        self.five.data.insert(word)
                else:
                    if self.five is None:
                        self.five = Trie('')
                        self.five.insert(seq[1:], word)
                    else:
                        self.five.insert(seq[1:], word)
            case '6':
                if len(seq) == 1:
                    if self.six is None:
                        self.six = Trie(word)
                    else:
                        self.six.data.insert(word)
                else:
                    if self.six is None:
                        self.six = Trie('')
                        self.six.insert(seq[1:], word)
                    else:
                        self.six.insert(seq[1:], word)
            case '7':
                if len(seq) == 1:
                    if self.seven is None:
                        self.seven = Trie(word)
                    else:
                        self.seven.data.insert(word)
                else:
                    if self.seven is None:
                        self.seven = Trie('')
                        self.seven.insert(seq[1:], word)
                    else:
                        self.seven.insert(seq[1:], word)
            case '8':
                if len(seq) == 1:
                    if self.eight is None:
                        self.eight = Trie(word)
                    else:
                        self.eight.data.insert(word)
                else:
                    if self.eight is None:
                        self.eight = Trie('')
                        self.eight.insert(seq[1:], word)
                    else:
                        self.eight.insert(seq[1:], word)
            case '9':
                if len(seq) == 1:
                    if self.nine is None:
                        self.nine = Trie(word)
                    else:
                        self.nine.data.insert(word)
                else:
                    if self.nine is None:
                        self.nine = Trie('')
                        self.nine.insert(seq[1:], word)
                    else:
                        self.nine.insert(seq[1:], word)

    def get_words(self, seq, container):
        try:
            if not len(seq) == 1:
                if seq[0] == '2':
                    return self.two.get_words(seq[1:], container)
                elif seq[0] == '3':
                    return self.three.get_words(seq[1:], container)
                elif seq[0] == '4':
                    return self.four.get_words(seq[1:], container)
                elif seq[0] == '5':
                    return self.five.get_words(seq[1:], container)
                elif seq[0] == '6':
                    return self.six.get_words(seq[1:], container)
                elif seq[0] == '7':
                    return self.seven.get_words(seq[1:], container)
                elif seq[0] == '8':
                    return self.eight.get_words(seq[1:], container)
                elif seq[0] == '9':
                    return self.nine.get_words(seq[1:], container)
            else:
                if seq == '2':
                    return self.words_below(self.two, container)
                elif seq == '3':
                    return self.words_below(self.three, container)
                elif seq == '4':
                    return self.words_below(self.four, container)
                elif seq == '5':
                    return self.words_below(self.five, container)
                elif seq == '6':
                    return self.words_below(self.six, container)
                elif seq == '7':
                    return self.words_below(self.seven, container)
                elif seq == '8':
                    return self.words_below(self.eight, container)
                elif seq == '9':
                    return self.words_below(self.nine, container)
        except AttributeError:
            return []

    def words_below(self, root, container):
        container.extend(root.data.get_word_list())
        if root.two is not None:
            container.extend(root.two.data.get_word_list())
            self.words_below(root.two, container)
        if root.three is not None:
            container.extend(root.three.data.get_word_list())
            self.words_below(root.three, container)
        if root.four is not None:
            container.extend(root.four.data.get_word_list())
            self.words_below(root.four, container)
        if root.five is not None:
            container.extend(root.five.data.get_word_list())
            self.words_below(root.five, container)
        if root.six is not None:
            container.extend(root.six.data.get_word_list())
            self.words_below(root.six, container)
        if root.seven is not None:
            container.extend(root.seven.data.get_word_list())
            self.words_below(root.seven, container)
        if root.eight is not None:
            container.extend(root.eight.data.get_word_list())
            self.words_below(root.eight, container)
        if root.nine is not None:
            container.extend(root.nine.data.get_word_list())
            self.words_below(root.nine, container)
        return container

    def show(self):
        self.data.print()


if __name__ == "__main__":
    DICTIONARY = Trie('')

# Testinggggg
    with open('MITwordlist.10000.txt') as file:
        while line := file.readline().rstrip().lower():
            if line.isalpha():
                DICTIONARY.insert(word_to_seq(line), line)
            else:
                continue

    words = []
    DICTIONARY.words_below(DICTIONARY.two, words)

    print(len(words))
    test = []
    print(len(DICTIONARY.get_words('2', test)))

