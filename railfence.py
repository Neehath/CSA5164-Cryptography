def rail_fence_encrypt(plaintext, num_rails):
    rail = [['' for _ in range(len(plaintext))] for _ in range(num_rails)]
    row, col = 0, 0
    direction_down = False
    for char in plaintext:
        rail[row][col] = char
        col += 1
        if row == 0 or row == num_rails - 1:
            direction_down = not direction_down
        row += 1 if direction_down else -1
    ciphertext = ''.join(''.join(rail[i]) for i in range(num_rails))
    return ciphertext

def rail_fence_decrypt(ciphertext, num_rails):
    rail = [['' for _ in range(len(ciphertext))] for _ in range(num_rails)]
    row, col = 0, 0
    direction_down = None
    for char in ciphertext:
        rail[row][col] = '*'
        col += 1
        if row == 0 or row == num_rails - 1:
            direction_down = not direction_down
        row += 1 if direction_down else -1
    index = 0
    for i in range(num_rails):
        for j in range(len(ciphertext)):
            if rail[i][j] == '*' and index < len(ciphertext):
                rail[i][j] = ciphertext[index]
                index += 1
    plaintext = ''
    row, col = 0, 0
    direction_down = None
    for _ in range(len(ciphertext)):
        plaintext += rail[row][col]
        col += 1
        if row == 0 or row == num_rails - 1:
            direction_down = not direction_down
        row += 1 if direction_down else -1
    return plaintext

num_rails = int(input("Enter the number of rails: "))
plaintext = input("Enter the plaintext: ").replace(" ", "").upper()
ciphertext = rail_fence_encrypt(plaintext, num_rails)
print("Encrypted text:", ciphertext)
decrypted_text = rail_fence_decrypt(ciphertext, num_rails)
print("Decrypted text:", decrypted_text)
