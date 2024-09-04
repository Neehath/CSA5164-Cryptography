import string

def generate_key_mapping():
    alphabet = string.ascii_lowercase
    shuffled_alphabet = "QWERTYUIOPLKJHGFDSAZXCVBNM".lower()  # Replace with your own shuffled alphabet
    key_mapping = dict(zip(alphabet, shuffled_alphabet))
    return key_mapping

def encrypt(text, key_mapping):
    result = ""
    for char in text:
        if char.islower():
            result += key_mapping.get(char, char)
        elif char.isupper():
            result += key_mapping.get(char.lower(), char.lower()).upper()
        else:
            result += char
    return result

def decrypt(text, key_mapping):
    reversed_key_mapping = {v: k for k, v in key_mapping.items()}
    return encrypt(text, reversed_key_mapping)

key_mapping = generate_key_mapping()

text = input("Enter the text: ")

encrypted_text = encrypt(text, key_mapping)
print("Encrypted text:", encrypted_text)

decrypted_text = decrypt(encrypted_text, key_mapping)
print("Decrypted text:", decrypted_text)
