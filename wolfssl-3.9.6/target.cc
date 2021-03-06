#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <sys/stat.h>
#include <wolfssl/ssl.h>

const char *CA_PEM =
"-----BEGIN RSA PRIVATE KEY-----\n"
"MIIEogIBAAKCAQEAmv9Hz30laLagIEZWu8pJ7xfOFyQlm/peroUw3MmNyPCfXx/H"
"YruOkyDF2MLsGf5x4ynQeCs6ipNyrxZ8oSz73DHJSOUaVrzFFVKy+y1Y3huLgczH"
"DHwPAEqwSN4z8ND48Gio2UfG9mRTGjPq3J94b6HKcXz/fJLtrQhBTxnXcHTWmt46"
"RxbqRbWkz68dw9LW5plZqhsXi0P0D1jLtcrzHe2t4DwCZs/xf2kifSlDNc/Dimij"
"XxFCjRB5mr1zR/4l5teFkStGSdwKhFOY5IzrNAy+yHgE0zDwysoo/kax+XKLTnP/"
"p3135a1uNbU+M8UKhZFHpdJJTRfaOG1tKK2XvQIDAQABAoIBAAf4XI701nmd+nnu"
"ZANgEZEz3isedriglUHQI4UW8C2HAgr4LV6MWnaCVuogi9eCWATgX5HuVyJNFrae"
"J2Z6U7Es9jbDYSlYp6HDEOUNneY98FyKVSn1LyhKrunwUyds94AVQal6oWaGHifY"
"x5j0slK7NRfE37ZeL86YABO7NnLX2rmyOTrdaXtxl4LEb2bo9NjjFOwR7N//pWPX"
"Uhho+dKxKUJ5kY4WvVEXfWqHRFuz6svSG6ot/sbHTobQ3hxaKuSq8fKoRBGtwlri"
"6tPaFoPufLfdvQUgOuAjsqfgytVxE4ZwexFVNnhk+qsYyB+G0bwPVwuckNPfzDs0"
"X0BWTRkCgYEAzhtQ8nSsRWqCuMWiIJrRoJc92vGbwT6HYZQDvBA3tx9QO6cATDOY"
"f8zVbC39JtuZhxxojDBKQZ9FZnIswwxqiA4qRZ2CK9yKrPTxfh8tdhBMg8xHl7it"
"pGFXCitm2xHkxmiebvF8yuxLurzny2GsEuLvGYepWepBDgLUV4a0u9cCgYEAwISl"
"NwbvZ0KUsRBIrx5XrZYCeq7cjLIveg9oqi3GHN/Zw/0okQDn4OwYw1+uPxIGVzBm"
"h5aSD02nbKKcKiOM/TG4JFS6EGdn2S5bIzh3IWznh9WQh6AdgY8Vn7EJQw9dr6og"
"MyMQ8m943YzmHsfYwfAJGplAc2D36P/r2d7t9osCgYA3gd/RDF8A6uh9vqwlP8zJ"
"BTJhbsRVzPNE8kn3Mh7vMH25Mwa/fv3JHW81DUWqW2YDn0EA0FiPR8e3CXTIquVd"
"8wKrcPoHugOXBPis0NS7gTQ6Ip/9Wn1ZUeXRFVNEGJOWY8KXem3zcKQMjKeYfJuN"
"EpT2OTUAxDf1AAoT8HFoTQKBgA/sqPHlS/ZBpqUC0NBTdTMxnmDhh/LHZm/1SFYT"
"VTjcN1oj3bAo4AVV4jJ+/p3O8uFRapm6lbhYVwoAZWSC7k2fSDkRHRbwRsHLONSv"
"/gKwzHIK81qUnvwxhrtf3IFEix5VtzYjp2o2WEwTNJHFPCPGpCokFRW2JquKR8sM"
"yqhDAoGAX1IayKXhTzcWr4VucYAiP8InRubvotIjBU0dbdt9br1mPuf15YxYN6FU"
"5i6B7uvmD08Soq1DXzjPUGBTD24bgpv3/f3JLkOdXJbQkvLydIWDEHr50PkGkGQR"
"h5X5sb3H5YqMLVeZmGGF5TonntCG5RdODb8PH7w4+F+ryWYpP1k=\n"
"-----END RSA PRIVATE KEY-----\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIDoTCCAomgAwIBAgIJAMLR+JGdALbnMA0GCSqGSIb3DQEBCwUAMGcxCzAJBgNV"
"BAYTAmNhMQswCQYDVQQIDAJjYTELMAkGA1UEBwwCY2ExCzAJBgNVBAoMAmNhMQsw"
"CQYDVQQLDAJjYTELMAkGA1UEAwwCY2ExFzAVBgkqhkiG9w0BCQEWCGNhQGNhLmNh"
"MB4XDTE2MDcyNzA2MjAwN1oXDTE3MDcyNzA2MjAwN1owZzELMAkGA1UEBhMCY2Ex"
"CzAJBgNVBAgMAmNhMQswCQYDVQQHDAJjYTELMAkGA1UECgwCY2ExCzAJBgNVBAsM"
"AmNhMQswCQYDVQQDDAJjYTEXMBUGCSqGSIb3DQEJARYIY2FAY2EuY2EwggEiMA0G"
"CSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQCa/0fPfSVotqAgRla7yknvF84XJCWb"
"+l6uhTDcyY3I8J9fH8diu46TIMXYwuwZ/nHjKdB4KzqKk3KvFnyhLPvcMclI5RpW"
"vMUVUrL7LVjeG4uBzMcMfA8ASrBI3jPw0PjwaKjZR8b2ZFMaM+rcn3hvocpxfP98"
"ku2tCEFPGddwdNaa3jpHFupFtaTPrx3D0tbmmVmqGxeLQ/QPWMu1yvMd7a3gPAJm"
"z/F/aSJ9KUM1z8OKaKNfEUKNEHmavXNH/iXm14WRK0ZJ3AqEU5jkjOs0DL7IeATT"
"MPDKyij+RrH5cotOc/+nfXflrW41tT4zxQqFkUel0klNF9o4bW0orZe9AgMBAAGj"
"UDBOMB0GA1UdDgQWBBSM6idosC4pnTs7LQXPU00aDrJzfDAfBgNVHSMEGDAWgBSM"
"6idosC4pnTs7LQXPU00aDrJzfDAMBgNVHRMEBTADAQH/MA0GCSqGSIb3DQEBCwUA"
"A4IBAQBmBxPWcW4NzUAsKZ41mqzcPgR431AFz7A//LegdOS0xSbDBeEnLZwMEqlh"
"pK+Mu/k6GMRIZFF7a4SOZbTbqOdHzSvNhnm2MAZWVsNW58EJs+ymMf1U1URA8I47"
"ZL9NUnm117POVHwqVofGu5eQOMwAQQwb2J6Ovlid/zsLMaZphOF+femFuUIgO7Lb"
"QeYMFn9AfhXu0YSwAL1S3ISReqBo65V0NiQiDKEVC+sKsSvoJk88JlDeVrkwFz38"
"jT8C38Vjjv4yAwdgqPaU1pHCa/JtA4M0TtBZBHktGmtpnd6ElbiunItfuhvMtcVq"
"t5P55qzDigzxXbFmNOGt5h8C/dhB\n"
"-----END CERTIFICATE-----\n";

static int verify_cert_mem(const uint8_t *certfile, uint32_t size_cert,
                           const uint8_t *cafile, uint32_t size_ca)
{
    int ret = -1;
    int filetype = SSL_FILETYPE_PEM;

    WOLFSSL_CERT_MANAGER *cm = NULL;

    ret = wolfSSL_Init();
    if (ret != SSL_SUCCESS)
        goto out;


    cm = wolfSSL_CertManagerNew();
    if (cm == NULL) {
        return EXIT_FAILURE;
    }

    ret = wolfSSL_CertManagerLoadCABuffer(cm,
                                          cafile,
                                          size_ca,
                                          filetype);

    if (ret != SSL_SUCCESS) {
        goto out;
    }

    ret = wolfSSL_CertManagerVerifyBuffer(cm,
                                          certfile,
                                          size_cert,
                                          filetype);
    if (ret != SSL_SUCCESS) {
        goto out;
    }

    ret = 0;

out:
    wolfSSL_CertManagerUnloadCAs(cm);
    wolfSSL_CertManagerFree(cm);
    wolfSSL_Cleanup();
    return ret;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *cert_data,
                                      size_t cert_sz) {
    verify_cert_mem(cert_data, cert_sz, (uint8_t *)CA_PEM, strlen(CA_PEM));
    return 0;
}
