#include <main.h>
#include <crypto/block.h>

int main()
{
        unsigned char blkheader[100];
        hex2bin("0001002025261447a590dcab7390e0152cb29387833f4a2279bd518e81eae57e55b2ec4df40d39bfdb0965dc9e6d5ce7d0d52d6fe15d814364b24234f0b6e07b7d3c5dcfc569655d7c931a1c06b9abcccfcd62524b9dc530dda240d3a917c08420cf0200", 200, blkheader);

        // print input header
        for (unsigned int i = 0; i < 100; i++)
          printf("%02hhx", blkheader[i]);
        printf("\n");

        // do pow hash
        CBlockHeader block;
        memcpy(reinterpret_cast<unsigned char*>(&block), blkheader, 100);
        uint256 powhash = block.GetPoWHash();

        // print pow hash result
        unsigned char blkhashout[32];
	unsigned char blkcmix[16];
        memcpy(blkhashout,reinterpret_cast<unsigned char*>(&powhash),32);
        for (unsigned int i = 0; i < 32; i++)
          printf("%02hhx", blkhashout[i]);
        printf("\n");

        // iterate byte like nonce
        unsigned int x = 0;
        while (x < 255)
        {
            blkheader[0] = x;
            memcpy(reinterpret_cast<unsigned char*>(&block), blkheader, 100);
            uint256 powhash = block.GetPoWHash();
            uint128 cmix = block.GetCMix();

            memcpy(blkhashout,reinterpret_cast<unsigned char*>(&powhash),32);
            for (unsigned int i = 0; i < 32; i++)
              printf("%02hhx", blkhashout[i]);
            printf("\n");

            memcpy(blkcmix,reinterpret_cast<unsigned char*>(&cmix),16);
            for (unsigned int i = 0; i < 16; i++)
              printf("%02hhx", blkcmix[i]);
            printf("\n");

            x++;
        }

	return(0);
}
