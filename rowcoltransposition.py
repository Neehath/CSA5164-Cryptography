def create_matrix(plaintext, num_cols):
    num_rows = (len(plaintext) + num_cols - 1) // num_cols
    matrix = [['' for _ in range(num_cols)] for _ in range(num_rows)]
    for i in range(len(plaintext)):
        row = i // num_cols
        col = i % num_cols
        matrix[row][col] = plaintext[i]
    return matrix

def encrypt(plaintext, key):
    num_cols = len(key)
    matrix = create_matrix(plaintext, num_cols)
    ciphertext = ''
    for col in sorted(range(num_cols), key=lambda k: key.index(str(k + 1))):
        for row in range(len(matrix)):
            if matrix[row][col] != '':
                ciphertext += matrix[row][col]
    return ciphertext

def decrypt(ciphertext, key):
    num_cols = len(key)
    num_rows = (len(ciphertext) + num_cols - 1) // num_cols
    matrix = [['' for _ in range(num_cols)] for _ in range(num_rows)]
    index = 0
    for col in sorted(range(num_cols), key=lambda k: key.index(str(k + 1))):
        for row in range(num_rows):
            if index < len(ciphertext):
                matrix[row][col] = ciphertext[index]
                index += 1
    plaintext = ''
    for row in range(num_rows):
        for col in range(num_cols):
            if matrix[row][col] != '':
                plaintext += matrix[row][col]
    return plaintext

# Example usage
key = input("Enter the key (column order as numbers, e.g., '3142'): ")
plaintext = input("Enter the plaintext: ").replace(" ", "").upper()

ciphertext = encrypt(plaintext, key)
print("Encrypted text:", ciphertext)

decrypted_text = decrypt(ciphertext, key)
print("Decrypted text:", decrypted_text)
