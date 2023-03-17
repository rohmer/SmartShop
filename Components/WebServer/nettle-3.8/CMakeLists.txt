cmake_minimum_required(VERSION 3.18)
SET(PROJECT_NAME "nettle")
project($PROJECT_NAME VERSION 3.8)

if(NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/version.h)
message("Configuring nettle...")
exec_program("bash ${CMAKE_CURRENT_SOURCE_DIR}/configure" 
RESULT_VARIABLE result
           OUTPUT_VARIABLE output
           )
message("RESULT: " ${result})
message("OUTPUT: " ${output})
endif()

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
target_include_directories(nettle PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

file(GLOB hogweedsrc
	sexp.c sexp-format.c 
		sexp-transport.c sexp-transport-format.c 
		bignum.c bignum-random.c bignum-random-prime.c 
		sexp2bignum.c 
		pkcs1.c pkcs1-encrypt.c pkcs1-decrypt.c 
		pkcs1-sec-decrypt.c 
		pkcs1-rsa-digest.c pkcs1-rsa-md5.c pkcs1-rsa-sha1.c 
		pkcs1-rsa-sha256.c pkcs1-rsa-sha512.c 
		pss.c pss-mgf1.c 
		rsa.c rsa-sign.c rsa-sign-tr.c rsa-verify.c 
		rsa-sec-compute-root.c 
		rsa-pkcs1-sign.c rsa-pkcs1-sign-tr.c rsa-pkcs1-verify.c 
		rsa-md5-sign.c rsa-md5-sign-tr.c rsa-md5-verify.c 
		rsa-sha1-sign.c rsa-sha1-sign-tr.c rsa-sha1-verify.c 
		rsa-sha256-sign.c rsa-sha256-sign-tr.c rsa-sha256-verify.c 
		rsa-sha512-sign.c rsa-sha512-sign-tr.c rsa-sha512-verify.c 
		rsa-pss-sha256-sign-tr.c rsa-pss-sha256-verify.c 
		rsa-pss-sha512-sign-tr.c rsa-pss-sha512-verify.c 
		rsa-encrypt.c rsa-decrypt.c 
		rsa-sec-decrypt.c rsa-decrypt-tr.c 
		rsa-keygen.c rsa-blind.c 
		rsa2sexp.c sexp2rsa.c 
		dsa.c dsa-compat.c dsa-compat-keygen.c dsa-gen-params.c 
		dsa-sign.c dsa-verify.c dsa-keygen.c dsa-hash.c 
		dsa-sha1-sign.c dsa-sha1-verify.c 
		dsa-sha256-sign.c dsa-sha256-verify.c  
		dsa2sexp.c sexp2dsa.c 
		pgp-encode.c rsa2openpgp.c 
		der-iterator.c der2rsa.c der2dsa.c 
		sec-add-1.c sec-sub-1.c sec-tabselect.c 
		gmp-glue.c cnd-copy.c 
		ecc-mod.c ecc-mod-inv.c 
		ecc-mod-arith.c ecc-pp1-redc.c ecc-pm1-redc.c 
		ecc-curve25519.c ecc-curve448.c 
		ecc-gost-gc256b.c ecc-gost-gc512a.c 
		ecc-secp192r1.c ecc-secp224r1.c ecc-secp256r1.c 
		ecc-secp384r1.c ecc-secp521r1.c 
		ecc-size.c ecc-j-to-a.c ecc-a-to-j.c 
		ecc-dup-jj.c ecc-add-jja.c ecc-add-jjj.c 
		ecc-eh-to-a.c 
		ecc-dup-eh.c ecc-add-eh.c ecc-add-ehh.c 
		ecc-dup-th.c ecc-add-th.c ecc-add-thh.c 
		ecc-mul-g-eh.c ecc-mul-a-eh.c ecc-mul-m.c 
		ecc-mul-g.c ecc-mul-a.c ecc-hash.c ecc-random.c 
		ecc-point.c ecc-scalar.c ecc-point-mul.c ecc-point-mul-g.c 
		ecc-ecdsa-sign.c ecdsa-sign.c 
		ecc-ecdsa-verify.c ecdsa-verify.c ecdsa-keygen.c 
		ecc-gostdsa-sign.c gostdsa-sign.c 
		ecc-gostdsa-verify.c gostdsa-verify.c gostdsa-vko.c 
		curve25519-mul-g.c curve25519-mul.c curve25519-eh-to-x.c 
		curve448-mul-g.c curve448-mul.c curve448-eh-to-x.c 
		eddsa-compress.c eddsa-decompress.c eddsa-expand.c 
		eddsa-hash.c eddsa-pubkey.c eddsa-sign.c eddsa-verify.c 
		ed25519-sha512.c ed25519-sha512-pubkey.c 
		ed25519-sha512-sign.c ed25519-sha512-verify.c 
		ed448-shake256.c ed448-shake256-pubkey.c 
		ed448-shake256-sign.c ed448-shake256-verify.c
)
add_library(hogweed SHARED ${hogweedsrc})