def generate_key_matrix(key):
    key = ''.join(sorted(set(key), key=key.index))
    key += ''.join([chr(i) for i in range(97, 123) if chr(i) not in key and chr(i) != 'j'])
    matrix = [list(key[i:i+5]) for i in range(0, 25, 5)]
    return matrix

def format_plaintext(plaintext):
    plaintext = plaintext.replace('j', 'i')
    formatted_text = ""
    i = 0
    while i < len(plaintext):
        a = plaintext[i]
        b = plaintext[i+1] if i+1 < len(plaintext) else 'x'
        if a == b:
            formatted_text += a + 'x'
            i += 1
        else:
            formatted_text += a + b
            i += 2
    if len(formatted_text) % 2 != 0:
        formatted_text += 'x'
    return formatted_text

def find_position(char, matrix):
    for i, row in enumerate(matrix):
        for j, letter in enumerate(row):
            if char == letter:
                return i, j
    return None

def encrypt_pair(a, b, matrix, decrypt=False):
    row_a, col_a = find_position(a, matrix)
    row_b, col_b = find_position(b, matrix)
    shift = -1 if decrypt else 1
    if row_a == row_b:
        return matrix[row_a][(col_a + shift) % 5] + matrix[row_b][(col_b + shift) % 5]
    elif col_a == col_b:
        return matrix[(row_a + shift) % 5][col_a] + matrix[(row_b + shift) % 5][col_b]
    else:
        return matrix[row_a][col_b] + matrix[row_b][col_a]

def encrypt(plaintext, key, decrypt=False):
    matrix = generate_key_matrix(key)
    plaintext = format_plaintext(plaintext)
    result = ""
    for i in range(0, len(plaintext), 2):
        a = plaintext[i]
        b = plaintext[i+1]
        result += encrypt_pair(a, b, matrix, decrypt)
    return result

key = input("Enter the key: ").replace(" ", "").lower()
plaintext = input("Enter the plaintext: ").replace(" ", "").lower()

ciphertext = encrypt(plaintext, key)
print("Encrypted text:", ciphertext)

decrypted_text = encrypt(ciphertext, key, decrypt=True)
print("Decrypted text:", decrypted_text)
