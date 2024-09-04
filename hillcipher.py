import numpy as np

def mod26(num):
    return num % 26

def matrix_inverse(matrix):
    determinant = int(np.round(np.linalg.det(matrix)))
    determinant_inv = pow(determinant, -1, 26)
    matrix_mod = np.round(determinant_inv * np.linalg.inv(matrix)).astype(int) % 26
    return matrix_mod

def matrix_to_string(matrix):
    return ''.join(chr(i + ord('A')) for i in matrix.flatten())

def string_to_matrix(text, size):
    matrix = [ord(c) - ord('A') for c in text]
    return np.array(matrix).reshape(size, size)

def encrypt(text, key):
    key_matrix = string_to_matrix(key, 2)
    text_matrix = string_to_matrix(text, 2)
    encrypted_matrix = np.dot(text_matrix, key_matrix) % 26
    return matrix_to_string(encrypted_matrix)

def decrypt(ciphertext, key):
    key_matrix = string_to_matrix(key, 2)
    key_matrix_inv = matrix_inverse(key_matrix)
    cipher_matrix = string_to_matrix(ciphertext, 2)
    decrypted_matrix = np.dot(cipher_matrix, key_matrix_inv) % 26
    return matrix_to_string(decrypted_matrix)

# Example usage
key = input("Enter the 2x2 key matrix (4 letters): ").upper().replace(" ", "")
plaintext = input("Enter the plaintext (must be an even length): ").upper().replace(" ", "")
ciphertext = encrypt(plaintext, key)
print("Encrypted text:", ciphertext)

decrypted_text = decrypt(ciphertext, key)
print("Decrypted text:", decrypted_text)
