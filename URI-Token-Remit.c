/**
 * 
 */
 
#include "hookapi.h"


// account buf builder ------------------------------------------------------------------------------
#define ACCOUNT_TO_BUF(buf_raw, i)\
{\
    unsigned char* buf = (unsigned char*)buf_raw;\
    *(uint64_t*)(buf + 0) = *(uint64_t*)(i +  0);\
    *(uint64_t*)(buf + 8) = *(uint64_t*)(i +  8);\
    *(uint32_t*)(buf + 16) = *(uint32_t*)(i + 16);\
}

// uri buffer builder ------------------------------------------------------------------------------
#define URI_TO_BUF(buf_raw, uri, len)\
{\
    unsigned char* buf = (unsigned char*)buf_raw;\
    for (int i = 0; GUARD(32), i < 32; ++i) \
        *(((uint64_t*)buf) + i) = *(((uint64_t*)uri) + i); \
    buf[len + 1] += 0xE1U; \
}

// byte settings for tx builder ------------------------------------------------------------------------------

// clang-format off
uint8_t txn[60000] =
{
/* size,upto */
/*   3,   0 */   0x12U, 0x00U, 0x5FU,                                                           /* tt = Remit       */
/*   5,   3 */   0x22U, 0x80U, 0x00U, 0x00U, 0x00U,                                          /* flags = tfCanonical */
/*   5,   8 */   0x24U, 0x00U, 0x00U, 0x00U, 0x00U,                                                 /* sequence = 0 */
/*   5,  13 */   0x99U, 0x99U, 0x99U, 0x99U, 0x99U,                                                /* dtag, flipped */
/*   6,  18 */   0x20U, 0x1AU, 0x00U, 0x00U, 0x00U, 0x00U,                                      /* first ledger seq */
/*   6,  24 */   0x20U, 0x1BU, 0x00U, 0x00U, 0x00U, 0x00U,                                       /* last ledger seq */
/*   9,  30 */   0x68U, 0x40U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,                         /* fee      */
/*  35,  39 */   0x73U, 0x21U, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,       /* pubkey   */
/*  22,  74 */   0x81U, 0x14U, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,                                  /* srcacc  */
/*  22,  96 */   0x83U, 0x14U, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,                                  /* dstacc  */
/* 116, 118 */   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    /* emit detail */
                 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,

/*   3, 234 */  0xE0U, 0x5CU, 0x75U,
/*   1, 237 */  0xE1U,
/*   0, 238 */                
};
// clang-format on

// TX BUILDER ------------------------------------------------------------------------------
#define BYTES_LEN 238U
#define FLS_OUT (txn + 20U)
#define LLS_OUT (txn + 26U)
#define DTAG_OUT (txn + 14U)
#define FEE_OUT (txn + 31U)
#define HOOK_ACC (txn + 76U)
#define OTX_ACC (txn + 98U)
#define URI_OUT (txn + 237U)
#define EMIT_OUT (txn + 118U)

// clang-format off
#define PREPARE_REMIT_TXN(account_buffer, dest_buffer, uri_buffer, uri_len) do { \ 
    etxn_reserve(1); \ 
    if (otxn_field(DTAG_OUT, 4, sfSourceTag) == 4) \
        *(DTAG_OUT - 1) = 0x2EU; \
    uint32_t fls = (uint32_t)ledger_seq() + 1; \ 
    *((uint32_t *)(FLS_OUT)) = FLIP_ENDIAN(fls); \ 
    uint32_t lls = fls + 4; \ 
    *((uint32_t *)(LLS_OUT)) = FLIP_ENDIAN(lls); \
    ACCOUNT_TO_BUF(HOOK_ACC, account_buffer); \ 
    ACCOUNT_TO_BUF(OTX_ACC, dest_buffer); \ 
    URI_TO_BUF(URI_OUT, uri_buffer, uri_len) \
    etxn_details(EMIT_OUT, 116U); \ 
    int64_t fee = etxn_fee_base(txn, BYTES_LEN + uri_len + 1); \ 
    uint8_t *b = FEE_OUT; \ 
    *b++ = 0b01000000 + ((fee >> 56) & 0b00111111); \ 
    *b++ = (fee >> 48) & 0xFFU; \ 
    *b++ = (fee >> 40) & 0xFFU; \ 
    *b++ = (fee >> 32) & 0xFFU; \ 
    *b++ = (fee >> 24) & 0xFFU; \ 
    *b++ = (fee >> 16) & 0xFFU; \ 
    *b++ = (fee >> 8) & 0xFFU; \ 
    *b++ = (fee >> 0) & 0xFFU; \
} while(0) 
// clang-format on

// HOOK ON ------------------------------------------------------------------------------
int64_t hook(uint32_t reserved) {
TRACESTR("URI TOKEN REMIT: Called.");

 // define and find hook account
 uint8_t hook_acct[20];
 hook_account(hook_acct, 20);

 // track incoming transaction to hook account
  int64_t tt = otxn_type();
  TRACEVAR(tt);



 

 
 // INVOKE ------------------------------------------------------------------------------

 

// define and set number buffer and key setting
uint8_t num_key[3] = {'N', 'U', 'M'};
uint8_t num_buffer[20] = {0x00U};
int8_t isNum = otxn_param(num_buffer, 1, SBUF(num_key));
 
// define and set uril buffer and key settings
uint8_t uril_buffer[8];
uint8_t uril_key[4] = { 'U', 'R', 'I', 'L' };
otxn_param(SBUF(uril_buffer), SBUF(uril_key));

//define uri key and arbatray buffer
uint8_t uri_key[3] = { 'U', 'R', 'I' };
uint8_t uri_buffer[256];
 
//define and set uri delete key and arbatray uri buffer
uint8_t del_key[3] = {'D', 'E', 'L'};
uint8_t del_buffer[256];
int8_t isDel = otxn_param(del_buffer, 1, SBUF(del_key));

// SET URI PARAM TO NAMESPACE ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
if (tt == 99 && isNum == 1 && isDel != 1 && num_buffer[0] >= 0 ) {
accept(SBUF("URI TOKEN REMIT: ran invoke"), 1);
TRACEVAR(tt);
 
//find uri buffer lenght
otxn_param(SBUF(uril_buffer), SBUF(uril_key));
 
//set lenght variable to proper bytes format
uint64_t uri_len = UINT64_FROM_BUF(uril_buffer);
TRACEVAR(uri_len);
 
//correct uri buffer settings to accomidate uri lenght
uri_buffer[0] = uri_len;

//set uri buffer and key settings
otxn_param(uri_buffer + 1, uri_len, SBUF(uri_key));
TRACEHEX(uri_buffer);
 
//
state_set(SBUF(uri_buffer), num_buffer, 32);
accept(SBUF("URI TOKEN REMIT: ran invoke"), 1);


 
 //SET DST BUFFER and KEY  ----------------------------------------------------------------------------
uint8_t dest_acc[20];
uint8_t dest_key[3] = { 'D', 'S', 'T' };
 if (otxn_param(SBUF(dest_acc), SBUF(dest_key)) != 20)
   {
      rollback(SBUF("URI TOKEN REMIT: Invalid Txn Parameter `DST`"), __LINE__);
   }
    TRACEHEX(dest_acc);


// PAYMENT ------------------------------------------------------------------------------


    accept(SBUF("URI TOKEN REMIT: ran payment"), 2);

    PREPARE_REMIT_TXN(hook_acct, dest_acc, uri_buffer, uri_len);

    // TXN: Emit/Send Txn
    uint8_t emithash[32];
    int64_t emit_result = emit(SBUF(emithash), txn, BYTES_LEN + uri_len + 1);
    if (emit_result > 0)
    {
        accept(SBUF("URI TOKEN REMIT: Tx emitted success."), __LINE__);
    }
    accept(SBUF("URI TOKEN REMIT: Tx emitted failure."), __LINE__);

}



    _g(1,1);
    return 0;
}
