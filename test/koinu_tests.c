/**********************************************************************
 * Copyright (c) 2022 bluezr & jaxlotl                                *
 * Copyright (c) 2022 The Dogecoin Foundation                         *
 * Distributed under the MIT software license, see the accompanying   *
 * file COPYING or http://www.opensource.org/licenses/mit-license.php.*
 **********************************************************************/

#include "utest.h"

#include <dogecoin/koinu.h>
#include <dogecoin/mem.h>
#include <dogecoin/utils.h>

void test_koinu() {
    /* stress test conversion between coins and koinu, round values */
    long double coin_amounts[] = { 0e-9, 1.0e-8,
                                    1.0e-7, 1.0e-6,
                                    1.0e-5, 1.0e-4,
                                    1.0e-3, 1.0e-2,
                                    1.0e-1, 1.0,
                                    1.0e1, 1.0e2,
                                    1.0e3, 1.0e4,
                                    1.0e5, 1.0e6,
                                    1.0e7, 1.0e8,
                                    1.0e9, 1.0e10,
                                    1.0e11 };

    uint64_t exp_answers[] = { 0UL, 1UL,
                                    10UL, 100UL,
                                    1000UL, 10000UL,
                                    100000UL, 1000000UL,
                                    10000000UL, 100000000UL,
                                    1000000000UL, 10000000000UL,
                                    100000000000UL, 1000000000000UL,
                                    10000000000000UL, 100000000000000UL,
                                    1000000000000000UL, 10000000000000000UL,
                                    100000000000000000UL, 1000000000000000000UL,
                                    10000000000000000000UL };

    uint64_t actual_answer;
    uint64_t diff;
    long double tmp;
    int i = 0;
    for (; i < 20; i++) {
        tmp = koinu_to_coins(exp_answers[i]);
        actual_answer = coins_to_koinu(tmp);
        u_assert_double_eq(tmp, coin_amounts[i]);
        u_assert_uint32_eq(actual_answer, exp_answers[i]);
#ifdef WIN32
        debug_print("T%d\n\tcoin_amt: %.8Lf\n\texpected: %"PRIu64"\n\tactual: %"PRIu64"\n\n", i, coin_amounts[i], exp_answers[i], actual_answer);
#else
        debug_print("T%d\n\tcoin_amt: %.8Lf\n\texpected: %"PRIu64"\n\tactual:   %"PRIu64"\n\n", i, coin_amounts[i], exp_answers[i], actual_answer);
#endif
        diff = (exp_answers[i] - actual_answer);
        u_assert_int_eq((int)diff, 0);
        }

    uint64_t actual_answer2;
    /* stress test conversion between coins and koinu, random decimal values */
    char* coin_amounts_str[] = { "183447094.020691168","410357585.029255459",
                                    "183447094.420691168","410357585.329255459",
                                    "567184894.440967455","1560227520.732426502",
                                    "2022535766.086211412","2047466422.707290167",
                                    "2487544599.240327145","4290779746.000111747",
                                    "4586257992.471687504","4660625607.783409803",
                                    "4766962398.856681418","5123141607.642632654",
                                    "5432527055.762317749","5778056333.994872841",
                                    "6654278072.590832439","7037268658.778085185",
                                    "7237308828.705953093","8606987445.409636773",
                                    "9100595327.168318456","9674059614.504642487",
                                    "1183447094.420691168","1410357585.329255459",
                                    "1567184894.440967455","11560227520.732426502",
                                    "12022535766.086211412","12047466422.707290167",
                                    "12487544599.240327145","14290779746.000111747",
                                    "14586257992.471687504","14660625607.783409803",
                                    "14766962398.856681418","15123141607.642632654",
                                    "15432527055.762317749","15778056333.994872841",
                                    "16654278072.590832439","17037268658.778085185",
                                    "17237308828.705953093","18606987445.409636773",
                                    "19100595327.168318456","19674059614.504642487" };

    /* stress test conversion between coins and koinu, random decimal values */
    char* coin_amounts_expected[] = { "183447094.02069116","410357585.02925545",
                                        "183447094.42069116","410357585.32925545",
                                        "567184894.44096745","1560227520.73242650",
                                        "2022535766.08621141","2047466422.70729016",
                                        "2487544599.24032714","4290779746.00011174",
                                        "4586257992.47168750","4660625607.78340980",
                                        "4766962398.85668141","5123141607.64263265",
                                        "5432527055.76231774","5778056333.99487284",
                                        "6654278072.59083243","7037268658.77808518",
                                        "7237308828.70595309","8606987445.40963677",
                                        "9100595327.16831845","9674059614.50464248",
                                        "1183447094.42069116","1410357585.32925545",
                                        "1567184894.44096745","11560227520.73242650",
                                        "12022535766.08621141","12047466422.70729016",
                                        "12487544599.24032714","14290779746.00011174",
                                        "14586257992.47168750","14660625607.78340980",
                                        "14766962398.85668141","15123141607.64263265",
                                        "15432527055.76231774","15778056333.99487284",
                                        "16654278072.59083243","17037268658.77808518",
                                        "17237308828.70595309","18606987445.40963677",
                                        "19100595327.16831845","19674059614.50464248" };

    uint64_t exp_answers2[] = { 18344709402069116, 41035758502925545,
                                    18344709442069116, 41035758532925545,
                                    56718489444096745, 156022752073242650,
                                    202253576608621141, 204746642270729016,
                                    248754459924032714, 429077974600011174,
                                    458625799247168750, 466062560778340980,
                                    476696239885668141, 512314160764263265,
                                    543252705576231774, 577805633399487284,
                                    665427807259083243, 703726865877808518,
                                    723730882870595309, 860698744540963677,
                                    910059532716831845, 967405961450464248,
                                    118344709442069116, 141035758532925545,
                                    156718489444096745, 1156022752073242650,
                                    1202253576608621141, 1204746642270729016,
                                    1248754459924032714, 1429077974600011174,
                                    1458625799247168750, 1466062560778340980,
                                    1476696239885668141, 1512314160764263265,
                                    1543252705576231774, 1577805633399487284,
                                    1665427807259083243, 1703726865877808518,
                                    1723730882870595309, 1860698744540963677,
                                    1910059532716831845, 1967405961450464248 };

    for (i = 0; i < 42; i++) {
        debug_print("\n-----------------------------------\nT%d build: %s\n------------------------------------\n", i, get_build());
        actual_answer2 = coins_to_koinu_str(coin_amounts_str[i]);
        char* coins1[21];
        dogecoin_mem_zero(coins1, 21);
        if (!koinu_to_coins_str(actual_answer2, (char*)coins1)) exit(EXIT_FAILURE);
        u_assert_str_eq((char*)coins1, coin_amounts_expected[i]);
        diff = exp_answers2[i] - actual_answer2;
        u_assert_uint32_eq(actual_answer2, exp_answers2[i]);
        u_assert_int_eq((int)diff, 0);
        debug_print("\n\n\tcoin_amt: %s\n\texpected: %"PRIu64"\n\tactual:   %"PRIu64"\n\n", coin_amounts_expected[i], exp_answers2[i], actual_answer2);
        }

    uint64_t actual_answer3;
    /* set of variable string length values */
    char* varlen_coin_amounts_str[] = { "10.0001", "1",
                                        "1.1","1.01",
                                        "1.001", "1.0001",
                                        "1.00001", "1.000001",
                                        "1.0000001", "1.00000001",
                                        "1fej.ioi929292", "12345678910",
                                        "-120202", "4893028948091289480183944",
                                        "0x5a", "abcdefghijklmnopqrstuvwxyz",
                                        "1000000000000.123456789" };

    char* varlen_exp_coin_amounts_str[] = { "10.00010000", "1.00000000",
                                            "1.10000000","1.01000000",
                                            "1.00100000", "1.00010000",
                                            "1.00001000", "1.00000100",
                                            "1.00000010", "1.00000001",
                                            "", "12345678910.00000000",
                                            "", "",
                                            "", "",
                                            "" };

    uint64_t exp_answers3[] = { 1000010000, 100000000,
                                110000000, 101000000,
                                100100000, 100010000,
                                100001000, 100000100,
                                100000010, 100000001,
                                0, 1234567891000000000,
                                0, 0,
                                0, 0,
                                0 };

    for (i = 0; i < 17; i++) {
        debug_print("\n-----------------------------------\nT%d build: %s\n------------------------------------\n", i, get_build());
        actual_answer3 = coins_to_koinu_str(varlen_coin_amounts_str[i]);
        char* coins2[21];
        dogecoin_mem_zero(coins2, 21);
        koinu_to_coins_str(actual_answer3, (char*)coins2);
        u_assert_str_eq((char*)coins2, varlen_exp_coin_amounts_str[i]);
        diff = exp_answers3[i] - actual_answer3;
        u_assert_uint32_eq(actual_answer3, exp_answers3[i]);
        u_assert_int_eq((int)diff, 0);
        debug_print("\n\n\tcoin_amt: %s\n\texpected: %"PRIu64"\n\tactual:   %"PRIu64"\n\n", varlen_coin_amounts_str[i], exp_answers3[i], actual_answer3);
        }

    uint64_t actual_answer4;
    /* max out values */
    char* maxout_coin_amounts_str[] = { "184467440737.09551615", "184467440737.09551616" };
    char* maxout_exp_coin_amounts_str[] = { "", "" };
    uint64_t exp_answers4[] = { 0, 0 };

    for (i = 0; i < 2; i++) {
        debug_print("\n-----------------------------------\nT%d build: %s\n------------------------------------\n", i, get_build());
        actual_answer4 = coins_to_koinu_str(maxout_coin_amounts_str[i]);
        char* coins3[21];
        dogecoin_mem_zero(coins3, 21);
        koinu_to_coins_str(actual_answer4, (char*)coins3);
        u_assert_str_eq((char*)coins3, maxout_exp_coin_amounts_str[i]);
        diff = exp_answers4[i] - actual_answer4;
        u_assert_uint32_eq(actual_answer4, exp_answers4[i]);
        u_assert_int_eq((int)diff, 0);
        debug_print("\n\n\tcoin_amt: %s\n\texpected: %"PRIu64"\n\tactual:   %"PRIu64"\n\n", maxout_coin_amounts_str[i], exp_answers4[i], actual_answer4);
        }
    }
