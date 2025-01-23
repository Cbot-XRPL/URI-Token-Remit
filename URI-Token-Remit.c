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


// START OF THE HOOK ACTIVATION -----------------------------------------------------------------------------------------


int64_t hook(uint32_t reserved) {

TRACESTR("uri_token_remit.c: Called.");

// ACCOUNT: Hook Account
uint8_t hook_acct[20];
hook_account(hook_acct, 20);

// ACCOUNT: Origin Tx Account
uint8_t otx_acc[20];
otxn_field(otx_acc, 20, sfAccount);

// To know the type of origin txn
int64_t tt = otxn_type();


// Configure State Storage Numbers -----------------------------------------------------------------------------------------

// URIL state number
uint64_t ulnum = 0x00000000000F423F;
uint8_t ulnum_buf[8] = {0};
UINT64_TO_BUF(ulnum_buf, ulnum);

// URI state number
uint64_t unum = 0x00000000000F423E;
uint8_t unum_buf[8] = {0};
UINT64_TO_BUF(unum_buf, unum);

// COST state number
uint64_t cnum = 0x00000000000F423D;
uint8_t cnum_buf[8] = {0};
UINT64_TO_BUF(cnum_buf, cnum);

// Lock state number
uint64_t lnum = 0x00000000000F423C;
uint8_t lnum_buf[8] = {0};
UINT64_TO_BUF(lnum_buf, lnum);


// Configure Params -----------------------------------------------------------------------------------------


uint8_t cost_buf[8];
uint8_t cost_key[4] = { 'C', 'O', 'S','T'};
int8_t isCost = otxn_param(SBUF(cost_buf), SBUF(cost_key));

uint8_t num_buf[8];
uint8_t num_key[3] = { 'N', 'U', 'M'};
int8_t isNum = otxn_param(SBUF(num_buf), SBUF(num_key));

uint8_t lock_buf[8];
uint8_t lock_key[4] = { 'L', 'O', 'C', 'K'};
int8_t isLock = otxn_param(SBUF(lock_buf), SBUF(lock_key));

uint8_t pass_buf[8];
uint8_t pass_key[4] = { 'P', 'A', 'S', 'S'};
int8_t isPass = otxn_param(SBUF(pass_buf), SBUF(pass_key));

uint8_t del_buf[8];
uint8_t del_key[3] = { 'D', 'E', 'L'};
int8_t isDel = otxn_param(SBUF(del_buf), SBUF(del_key));

uint8_t uril_buf[8];
uint8_t uril_key[4] = { 'U', 'R', 'I', 'L' };
int8_t isUril = otxn_param(SBUF(uril_buf), SBUF(uril_key));
uint64_t uri_len = UINT64_FROM_BUF(uril_buf);


// Configure URIL and URI ----------------------------------------------------------------


// URIL state buffer
 uint8_t ulbuf[8]={0};
 
// Check if hook URIL state
int8_t hasUril = state(SBUF(ulbuf), SBUF(ulnum_buf));
uint64_t reconstructed_uril_value = UINT64_FROM_BUF(ulbuf);
TRACEVAR(ulbuf)
TRACEVAR(reconstructed_uril_value);

uint8_t uri_buffer[256];
int8_t uri_key[3] = { 'U', 'R', 'I' };
int8_t isUri1 = otxn_param(SBUF(uri_buffer), SBUF(uri_key));

//check if has a uril prior to adding uri
if (hasUril < 0 && isUri1 > 0)
rollback(SBUF("Error: This hook is missing a URIL! Please add a URIL to start building this hook."), __LINE__); 

//fix uri buffer
uri_buffer[0] = uri_len;
int8_t isUri2 = otxn_param(uri_buffer + 1,reconstructed_uril_value, SBUF(uri_key));
TRACEVAR(isUri2)


// HOOK LOCK -----------------------------------------------------------------------------------------  


// Lock state buffer
 uint8_t lbuf[8]={0};
 
// Check if hook has LOCK state
int8_t isLocked = state(SBUF(lbuf), SBUF(lnum_buf));

// Check if the hook is locked
if (isLocked > 0 && isLock < 0){
TRACESTR("The hook is locked.");
uint64_t reconstructed_lbuf_value = UINT64_FROM_BUF(lbuf);
TRACEVAR(reconstructed_lbuf_value);
uint64_t reconstructed_pass_value = UINT64_FROM_BUF(pass_buf);
TRACEVAR(reconstructed_pass_value);

//Compare lock and passkey
 if(reconstructed_lbuf_value != reconstructed_pass_value){
rollback(SBUF("Error: Incorrect passkey!"), __LINE__);
}
TRACESTR("passkey hook is now unlocked.");
}

// HookOn: Invoke Set LOCK State -----------------------------------------------------------------------------------------


if (tt == 99 && isLock > 0){ 

TRACESTR("Ran invoke to set lock");
TRACEHEX(lnum);
TRACEHEX(lock_buf);

            //the data       //number key
   #define SBUF(str) (uint32_t)(str), sizeof(str)
if (state_set(SBUF(lock_buf), SBUF(lnum_buf)) < 0)
		rollback(SBUF("Error: Could not set LOCK state!"), 1);

accept(SBUF("Success: Set the LOCK state."), __LINE__);

}


// HookOn: Invoke Set COST State -----------------------------------------------------------------------------------------


if (tt == 99 && isCost > 0){ 

TRACEHEX(cnum);
TRACEHEX(cost_buf);

   #define SBUF(str) (uint32_t)(str), sizeof(str)
if (state_set(SBUF(cost_buf), SBUF(cnum_buf)) < 0)
		rollback(SBUF("Error: Could not set COST state!"), 1);

accept(SBUF("Success: Set the COST state."), __LINE__);

}


// HookOn: Invoke Set URIL State -----------------------------------------------------------------------------------------


if (tt == 99 && isUril > 0){ 

TRACEHEX(unum_buf);
TRACEHEX(uril_buf);

   #define SBUF(str) (uint32_t)(str), sizeof(str)
if (state_set(SBUF(uril_buf), SBUF(ulnum_buf)) < 0)
		rollback(SBUF("Error: could not set the URIL state!"), 1);

accept(SBUF("Success: Set the URIL state."), __LINE__);

}

    
// HookOn: Invoke Set URI State -----------------------------------------------------------------------------------------


if (tt == 99 && isUri2 > 0){
	
TRACEHEX(unum_buf);
TRACEHEX(uri_buffer);

   #define SBUF(str) (uint32_t)(str), sizeof(str)
if (state_set(SBUF(uri_buffer), SBUF(unum_buf)) < 0)
		rollback(SBUF("Error: could not set the URI state!"), 1);
 
accept(SBUF("Success: Set a URI state."), __LINE__);
}

// HookOn: Invoke Set NUM State -----------------------------------------------------------------------------------------

// Look for base URI
 uint64_t suri[256];
 suri[0] = reconstructed_uril_value;
int8_t foundUri = (state(SBUF(suri), SBUF(unum_buf)));
TRACEHEX(suri);
// Ensure there is a Uri

TRACEVAR(isNum);
TRACEVAR(foundUri);
if (tt == 99 && isNum > 0 && foundUri > 0){
	
TRACEHEX(num_buf);
TRACEHEX(suri);

   #define SBUF(str) (uint32_t)(str), sizeof(str)
if (state_set(SBUF(suri), SBUF(num_buf)) < 0)
		rollback(SBUF("Error: could not set the URI state!"), 1);
 
accept(SBUF("Success: Set a URI state."), __LINE__);
}else(accept(SBUF("fuckk"), __LINE__));


// HookOn: Invoke Delete State -----------------------------------------------------------------------------------------


if (tt == 99 && isDel > 0){

TRACEHEX(del_buf);

   #define SBUF(str) (uint32_t)(str), sizeof(str)
if (state_set(0,0, SBUF(del_buf)) < 0)
		rollback(SBUF("Error: could not delete state!"),__LINE__);

accept(SBUF("Success: Deleted the state."), __LINE__);

}



// HookOn: Incoming Payment Gateway  -----------------------------------------------------------------------------------------


if (tt == 00){ 


// COST state buffer
 uint8_t cbuf[8]={0};
 
// Check if hook hook COST state value
int8_t hasCost = state(SBUF(cbuf), SBUF(cnum_buf));

// Check if the hook has cost
if (hasCost > 0){
TRACESTR("The hook has a URI token cost.");
TRACEHEX(cbuf)

// fetch the sent Amount
unsigned char amount_buffer[48];
int64_t amount_len = otxn_field(SBUF(amount_buffer), sfAmount);
TRACEHEX(amount_buffer);


//Ensure the payment is XAH
if (amount_len != 8)
{
rollback(SBUF("Error: This hook only accepts XAH!"), __LINE__);
}

//recontruct amount sent and cost to compare them
uint64_t reconstructed_cbuf_value = UINT64_FROM_BUF(cbuf);
TRACEVAR(reconstructed_cbuf_value);
uint64_t reconstructed_amount_value = UINT64_FROM_BUF(amount_buffer);

//Compare payment amount and cost
if( reconstructed_amount_value == reconstructed_cbuf_value){
rollback(SBUF("Error: Incorrect payment amount!"), __LINE__);
}
TRACESTR("Payment amounts match.");
}

TRACESTR("Payment portion of this hook is now unlocked.");
}


// HookOn: URI Token Mint  -----------------------------------------------------------------------------------------


if (tt == 00){ 

// STATE NUMBER KEY
uint64_t snum = 0x0000000000000003;
uint8_t snum_buf[8] = {0};
UINT64_TO_BUF(snum_buf, snum);


// STATE URI BUFFER
 uint64_t suri[256];
 suri[0] = 14;
   
if (state(SBUF(suri), SBUF(snum_buf)) < 0)
		rollback(SBUF("Could not check state!"), 1);

TRACEHEX(suri);
    PREPARE_REMIT_TXN(hook_acct, otx_acc, suri, unum);

    // TXN: Emit/Send Txn
    uint8_t emithash[32];
    int64_t emit_result = emit(SBUF(emithash), txn, BYTES_LEN + unum + 1);
    if (emit_result > 0)
    {
        accept(SBUF("Success:Tx emitted success."), __LINE__);
    }
    accept(SBUF("Error: Tx emitted failure."), __LINE__);

}

//final gaurds

    _g(1,1);
    return 0;
}
