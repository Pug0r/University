import unittest
from main import reverse_polish_notation


class MyTestCase(unittest.TestCase):
    def test_is_valid_rpn(self):
        self.assertRaises(ValueError, reverse_polish_notation, 'a b c d * %')
        self.assertRaises(ValueError, reverse_polish_notation, '* 5 5 3 * 4')
        self.assertRaises(ValueError, reverse_polish_notation, '4 1 ^ 1 4 x - ')
        self.assertRaises(ValueError, reverse_polish_notation, '2 3 + 5,1 *')
        self.assertRaises(ValueError, reverse_polish_notation, 'a b c d * %')
        self.assertRaises(ValueError, reverse_polish_notation, '19 0 / ')
        self.assertRaises(ValueError, reverse_polish_notation, '1 6 * * * * 1 2')
        self.assertEqual(reverse_polish_notation('2 3 5 - 3 * -'), 8)
        self.assertEqual(reverse_polish_notation('7         8 + 3 4 + *'), 105)
        self.assertEqual(reverse_polish_notation('5 6 - 4 * 5 2 2                    * - -'), -5)
        self.assertEqual(reverse_polish_notation('35 39 - 10 2 ^ * 25 4 * 2 * -'), -600)
        self.assertEqual(reverse_polish_notation('36 sqrt'), 6)
        self.assertEqual(reverse_polish_notation('36 sqrt 18 - '), -12)


if __name__ == '__main__':
    unittest.main()
