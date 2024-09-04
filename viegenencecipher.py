def generate_key(plaintext, key):
    key = list(key)
    if len(plaintext) == len(key):
        return key
    else:
        for i in range(len(plaintext) - len(key)):
            key.append(key[i % len(key)])
    return "".join(key)

def encrypt(plaintext, key):
    key = generate_key(plaintext, key)
    ciphertext = []
    for i in range(len(plaintext)):
        if plaintext[i].isalpha():
            shift = (ord(plaintext[i].upper()) + ord(key[i].upper())) % 26
            ciphertext.append(chr(shift + ord('A')))
        else:
            ciphertext.append(plaintext[i])
    return "".join(ciphertext)

def decrypt(ciphertext, key):
    key = generate_key(ciphertext, key)
    plaintext = []
    for i in range(len(ciphertext)):
        if ciphertext[i].isalpha():
            shift = (ord(ciphertext[i].upper()) - ord(key[i].upper()) + 26) % 26
            plaintext.append(chr(shift + ord('A')))
        else:
            plaintext.append(ciphertext[i])
    return "".join(plaintext)

key = input("Enter the key: ").replace(" ", "").upper()
plaintext = input("Enter the plaintext: ").replace(" ", "").upper()

ciphertext = encrypt(plaintext, key)
print("Encrypted text:", ciphertext)

decrypted_text = decrypt(ciphertext, key)
print("Decrypted text:", decrypted_text)
