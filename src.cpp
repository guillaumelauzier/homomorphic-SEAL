#include <iostream>
#include <seal/seal.h>

using namespace std;
using namespace seal;

int main()
{
    // Create a SEAL context
    auto context = SEALContext::Create(SEAL_SEC_LEVEL_TYPE::BFV);

    // Generate keys
    KeyGenerator keygen(context);
    auto public_key = keygen.public_key();
    auto secret_key = keygen.secret_key();

    // Encryptor
    Encryptor encryptor(context, public_key);

    // Decryptor
    Decryptor decryptor(context, secret_key);

    // Evaluator
    Evaluator evaluator(context);

    // Plaintexts
    Plaintext plain1("1");
    Plaintext plain2("2");

    // Encrypted values
    Ciphertext encrypted1, encrypted2;
    encryptor.encrypt(plain1, encrypted1);
    encryptor.encrypt(plain2, encrypted2);

    // Perform computation
    evaluator.add(encrypted1, encrypted2, encrypted1);

    // Decrypt the result
    Plaintext plain_result;
    decryptor.decrypt(encrypted1, plain_result);

    cout << plain_result.to_string() << endl;

    return 0;
}
