#include "hookapi.h"
#include <stdint.h>

// Account builder for tx
#define ACCOUNT_TO_BUF(buf_raw, i)\
{\
    unsigned char* buf = (unsigned char*)buf_raw;\
    *(uint64_t*)(buf + 0) = *(uint64_t*)(i +  0);\
    *(uint64_t*)(buf + 8) = *(uint64_t*)(i +  8);\
    *(uint32_t*)(buf + 16) = *(uint32_t*)(i + 16);\
}

// URI buffer builder for tx
#define URI_TO_BUF(buf_raw, uri, len)\
{\
    unsigned char* buf = (unsigned char*)buf_raw;\
    for (int i = 0; GUARD(32), i < 32; ++i) \
        *(((uint64_t*)buf) + i) = *(((uint64_t*)uri) + i); \
    buf[len + 1] += 0xE1U; \
}





// clang-format off tx sizing
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

// TX BUILDER
#define BYTES_LEN 238U
#define FLS_OUT (txn + 20U)
#define LLS_OUT (txn + 26U)
#define DTAG_OUT (txn + 14U)
#define FEE_OUT (txn + 31U)
#define HOOK_ACC (txn + 76U)
#define OTX_ACC (txn + 98U)
#define URI_OUT (txn + 237U)
#define EMIT_OUT (txn + 118U)

// clang-format off prepare remit tx
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



// START OF THE HOOK ACTIVATION

int64_t hook(uint32_t reserved) {

TRACESTR("txn_remit_mint.c: Called.");

// ACCOUNT: Hook Account
uint8_t hook_acct[20];
hook_account(hook_acct, 20);

// ACCOUNT: Origin Tx Account
uint8_t otx_acc[20];
otxn_field(otx_acc, 20, sfAccount);


// To know the type of origin txn
int64_t tt = otxn_type();
TRACEVAR(tt)


// Configure Params

  uint8_t num_buf[8];
  uint8_t num_key[3] = { 'N', 'U', 'M'};
  int8_t isNum = otxn_param(SBUF(num_buf), SBUF(num_key));
  uint64_t num_len = UINT64_FROM_BUF(num_buf);



  uint8_t del_buf[8];
  uint8_t del_key[3] = { 'D', 'E', 'L'};
  int8_t isDel = otxn_param(SBUF(del_buf), SBUF(del_key));
  uint64_t del_len = UINT64_FROM_BUF(del_buf);
 

    uint8_t uril_buf[8];
    uint8_t uril_key[4] = { 'U', 'R', 'I', 'L' };
    uint8_t isUril = otxn_param(SBUF(uril_buf), SBUF(uril_key));
    uint64_t uri_len = UINT64_FROM_BUF(uril_buf);

    


    uint8_t uri_buffer[256];
    uri_buffer[0] = uri_len;
    uint8_t uri_key[3] = { 'U', 'R', 'I' };
    uint8_t isUri = otxn_param(uri_buffer + 1, uri_len, SBUF(uri_key));
    


   // HookOn: Invoke Set URIL State
    if (tt == 72){ 

TRACEHEX( num_buf);
TRACEHEX(uril_buf);

   #define SBUF(str) (uint32_t)(str), sizeof(str)
if (state_set(SBUF(uril_buf), SBUF(num_buf)) < 0)
		rollback(SBUF("Error: could not set state!"), 1);

accept(SBUF("txn_remit_mint.c: WE SET THE URIL"), __LINE__);

    }

  
    
   // HookOn: Invoke Set State
    if (tt == 99 && isNum > 0 && isDel <= 0){ 

TRACEHEX(num_buf);
TRACEHEX(uri_buffer);

   #define SBUF(str) (uint32_t)(str), sizeof(str)
if (state_set(SBUF(uri_buffer), SBUF(num_buf)) < 0)
		rollback(SBUF("Error: could not set state!"), 1);

accept(SBUF("txn_remit_mint.c: WE SET THE STATE."), __LINE__);



    }







    // HookOn: Invoke Delete State
    if (tt == 99 && isDel > 0){

TRACEHEX(del_buf);


   #define SBUF(str) (uint32_t)(str), sizeof(str)
if (state_set(0,0, SBUF(del_buf)) < 0)
		rollback(SBUF("Error: could not set state!"), 1);

accept(SBUF("txn_remit_mint.c: WE DELETED THE STATE."), __LINE__);



    }






// HookOn: Incoming Payment   HELP HERE -------------------------------------------------------------------------------------------
if (tt == 00){ 


// STATE NUMBER KEY
uint64_t snum = 0x0000000000000001;
uint8_t snum_buf[8] = {0};
UINT64_TO_BUF(snum_buf, snum);
TRACEHEX(snum_buf);

// STATE URIL
uint64_t suril = 0x000000000000000E;
uint8_t suril_buf[8] = {0};
UINT64_TO_BUF(suril_buf, suril);
TRACEHEX(suril_buf);


// STATE URI BUFFER
uint8_t suri[14];



#define SBUF(str) (uint32_t)(str), sizeof(str)
if (state(SBUF(suri), SBUF(snum_buf)) >= 0)
		rollback(SBUF("Error: could not read state!"), 1);

TRACEVAR(suri)

    PREPARE_REMIT_TXN(hook_acct, otx_acc, suri, suril);

    // TXN: Emit/Send Txn
    uint8_t emithash[32];
    int64_t emit_result = emit(SBUF(emithash), txn, BYTES_LEN + uri_len + 1);
    if (emit_result > 0)
    {
        accept(SBUF("txn_remit_mint.c: Tx emitted success."), __LINE__);
    }
    accept(SBUF("txn_remit_mint.c: Tx emitted failure."), __LINE__);

}


//final gaurds

    _g(1,1);
    return 0;
}
