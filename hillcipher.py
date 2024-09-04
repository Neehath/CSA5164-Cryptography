import numpy as np

def mod26(num):
    return num % 26

def matrix_to_string(matrix):
    return ''.join(chr(i + ord('A')) for i in matrix.flatten())

def string_to_matrix(text, size):
    if len(text) % size != 0:
        raise ValueError("Text length must be divisible by matrix size.")
    matrix = [ord(c) - ord('A') for c in text]
    return np.array(matrix).reshape(-1, size)

def encrypt(text, key):
    key_matrix = np.array(key).reshape(2, 2)
    text_matrix = string_to_matrix(text, 2)
    encrypted_matrix = np.dot(text_matrix, key_matrix) % 26
    print("Encryption - Key Matrix:\n", key_matrix)
    print("Encryption - Text Matrix:\n", text_matrix)
    print("Encryption - Encrypted Matrix:\n", encrypted_matrix)
    return matrix_to_string(encrypted_matrix)

def matrix_inverse(matrix):
    determinant = int(round(np.linalg.det(matrix))) % 26
    if np.gcd(determinant, 26) != 1:
        raise ValueError("The matrix is not invertible modulo 26.")
    determinant_inv = pow(determinant, -1, 26)
    matrix_adj = np.round(np.linalg.inv(matrix) * determinant).astype(int) % 26
    matrix_inv = (determinant_inv * matrix_adj) % 26
    print("Inverse - Determinant:", determinant)
    print("Inverse - Determinant Inverse:", determinant_inv)
    print("Inverse - Adjugate Matrix:\n", matrix_adj)
    print("Inverse - Inverse Matrix:\n", matrix_inv)
    return matrix_inv

def decrypt(ciphertext, key):
    key_matrix = np.array(key).reshape(2, 2)
    try:
        key_matrix_inv = matrix_inverse(key_matrix)
    except ValueError as e:
        raise ValueError("Decryption failed: " + str(e))
    cipher_matrix = string_to_matrix(ciphertext, 2)
    decrypted_matrix = np.dot(cipher_matrix, key_matrix_inv) % 26
    print("Decryption - Key Matrix Inverse:\n", key_matrix_inv)
    print("Decryption - Cipher Matrix:\n", cipher_matrix)
    print("Decryption - Decrypted Matrix:\n", decrypted_matrix)
    decrypted_text = matrix_to_string(decrypted_matrix)
    return decrypted_text.rstrip('X')  # Remove padding if added

def get_key():
    key_input = input("Enter the key matrix (4 space-separated integers): ").split()
    if len(key_input) != 4:
        raise ValueError("Key must contain exactly 4 integers.")
    return [int(k) for k in key_input]

def get_plaintext():
    plaintext = input("Enter the plaintext: ").upper()
    if len(plaintext) % 2 != 0:
        plaintext += 'X'  # Padding the plaintext to ensure it has an even length
    return plaintext

def main():
    try:
        key_input = get_key()
        plaintext = get_plaintext()

        print("Key Matrix:\n", np.array(key_input).reshape(2, 2))
        print("Plaintext:", plaintext)

        ciphertext = encrypt(plaintext, key_input)
        print("Encrypted text:", ciphertext)

        decrypted_text = decrypt(ciphertext, key_input)
        print("Decrypted text:", decrypted_text)

    except Exception as e:
        print("An error occurred:", e)

if __name__ == "__main__":
    main()
