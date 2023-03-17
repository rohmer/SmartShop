cmake_minimum_required(VERSION 3.18)
SET(PROJECT_NAME "nettle")
project($PROJECT_NAME VERSION 3.8)

message("Configuring nettle...")
exec_program("bash ${CMAKE_CURRENT_SOURCE_DIR}/configure" 
RESULT_VARIABLE result
           OUTPUT_VARIABLE output
           )
message("RESULT: " ${result})
message("OUTPUT: " ${output})

file(GLOB nettlesrc 
	aes-decrypt-internal.c 
	aes-decrypt.c 
	aes-decrypt-table.c
	aes128-decrypt.c 
	aes192-decrypt.c 
	aes256-decrypt.c 
	aes-encrypt-internal.c 
	aes-encrypt.c 
	aes-encrypt-table.c 
	aes128-encrypt.c aes192-encrypt.c aes256-encrypt.c 
	aes-invert-internal.c aes-set-key-internal.c 
	aes-set-encrypt-key.c aes-set-decrypt-key.c 
	aes128-set-encrypt-key.c aes128-set-decrypt-key.c 
	aes128-meta.c 
	aes192-set-encrypt-key.c aes192-set-decrypt-key.c 
	aes192-meta.c 
	aes256-set-encrypt-key.c aes256-set-decrypt-key.c 
	aes256-meta.c 
	nist-keywrap.c 
	arcfour.c arcfour-crypt.c 
	arctwo.c arctwo-meta.c blowfish.c blowfish-bcrypt.c 
	base16-encode.c base16-decode.c base16-meta.c 
	base64-encode.c base64-decode.c base64-meta.c 
	base64url-encode.c base64url-decode.c base64url-meta.c 
	buffer.c buffer-init.c 
	camellia-crypt-internal.c camellia-table.c 
	camellia-absorb.c camellia-invert-key.c 
	camellia128-set-encrypt-key.c camellia128-crypt.c 
	camellia128-set-decrypt-key.c 
	camellia128-meta.c 
	camellia192-meta.c 
	camellia256-set-encrypt-key.c camellia256-crypt.c 
	camellia256-set-decrypt-key.c 
	camellia256-meta.c 
	cast128.c cast128-meta.c 
	cbc.c cbc-aes128-encrypt.c cbc-aes192-encrypt.c cbc-aes256-encrypt.c 
	ccm.c ccm-aes128.c ccm-aes192.c ccm-aes256.c cfb.c 
	siv-cmac.c siv-cmac-aes128.c siv-cmac-aes256.c 
	cnd-memcpy.c 
	chacha-crypt.c chacha-core-internal.c 
	chacha-poly1305.c chacha-poly1305-meta.c 
	chacha-set-key.c chacha-set-nonce.c 
	ctr.c ctr16.c des.c des3.c 
	eax.c eax-aes128.c eax-aes128-meta.c 
	ghash-set-key.c ghash-update.c gcm.c gcm-aes.c 
	gcm-aes128.c gcm-aes128-meta.c 
	gcm-aes192.c gcm-aes192-meta.c 
	gcm-aes256.c gcm-aes256-meta.c 
	gcm-camellia128.c gcm-camellia128-meta.c 
	gcm-camellia256.c gcm-camellia256-meta.c 
	cmac.c cmac64.c cmac-aes128.c cmac-aes256.c cmac-des3.c 
	cmac-aes128-meta.c cmac-aes256-meta.c cmac-des3-meta.c 
	gost28147.c gosthash94.c gosthash94-meta.c 
	hmac.c hmac-gosthash94.c hmac-md5.c hmac-ripemd160.c 
	hmac-sha1.c hmac-sha224.c hmac-sha256.c hmac-sha384.c 
	hmac-sha512.c hmac-streebog.c hmac-sm3.c 
	hmac-md5-meta.c hmac-ripemd160-meta.c hmac-sha1-meta.c 
	hmac-sha224-meta.c hmac-sha256-meta.c hmac-sha384-meta.c 
	hmac-sha512-meta.c hmac-streebog-meta.c hmac-sm3-meta.c 
	knuth-lfib.c hkdf.c 
	md2.c md2-meta.c md4.c md4-meta.c 
	md5.c md5-compress.c md5-compat.c md5-meta.c 
	memeql-sec.c memxor.c memxor3.c 
	nettle-lookup-hash.c 
	nettle-meta-aeads.c nettle-meta-armors.c 
	nettle-meta-ciphers.c nettle-meta-hashes.c nettle-meta-macs.c 
	pbkdf2.c pbkdf2-hmac-gosthash94.c pbkdf2-hmac-sha1.c 
	pbkdf2-hmac-sha256.c pbkdf2-hmac-sha384.c pbkdf2-hmac-sha512.c 
	poly1305-aes.c poly1305-internal.c 
	realloc.c 
	ripemd160.c ripemd160-compress.c ripemd160-meta.c 
	salsa20-core-internal.c salsa20-crypt-internal.c 
	salsa20-crypt.c salsa20r12-crypt.c salsa20-set-key.c 
	salsa20-set-nonce.c 
	salsa20-128-set-key.c salsa20-256-set-key.c 
	sha1.c sha1-compress.c sha1-meta.c 
	sha256.c sha256-compress.c sha224-meta.c sha256-meta.c 
	sha512.c sha512-compress.c sha384-meta.c sha512-meta.c 
	sha512-224-meta.c sha512-256-meta.c 
	sha3.c sha3-permute.c 
	sha3-224.c sha3-224-meta.c sha3-256.c sha3-256-meta.c 
	sha3-384.c sha3-384-meta.c sha3-512.c sha3-512-meta.c 
	shake256.c 
	sm3.c sm3-meta.c 
	serpent-set-key.c serpent-encrypt.c serpent-decrypt.c 
	serpent-meta.c 
	streebog.c streebog-meta.c 
	twofish.c twofish-meta.c 
	umac-nh.c umac-nh-n.c umac-l2.c umac-l3.c 
	umac-poly64.c umac-poly128.c umac-set-key.c 
	umac32.c umac64.c umac96.c umac128.c 
	version.c 
	write-be32.c write-le32.c write-le64.c 
	yarrow256.c yarrow_key_event.c 
	xts.c xts-aes128.c xts-aes256.c
)
add_compile_definitions(HAVE_CONFIG_H)
add_library(nettle SHARED ${nettlesrc})
