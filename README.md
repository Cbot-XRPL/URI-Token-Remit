

## URI Token Mint Hook for Xahau Network


This hook is designed to automatically distribute URI Tokens (RWA or NFT) based on the Xahau hook rule engine. This hook could potentially replace a transfer agent, allowing users a secure way to get assets without a broker. This hook will essentially allow you to register unique assets for distribution at a Xahau address. Some potential assets that could be distributed based on this hook are art, real estate, tickets, and digital products. This hook is complaint with current NFT standard XLS-53 and will work with the upcoming Bidds marketplace. If you want roytlies paid on your sales you will also need Broker || Royalty hook when it become available. You can find our Xahau Art Vault example of this hook on Mainnet at [address] and our Concert Rental Tickets on testnet installed at [address]

## What Does This Hook do

The hook is installed on an account. The length of your URIs (in bytes) set through a parameter called URIL. URIs and their NUM can be added or removed from the hook state via invoke transactions. It is crucial that all URIs have the exact same length, as this consistency is key to the hook's functionality (more details on this below). You must specify the cost to charge users for minting a URI token. You may specify a royties amount to be paid and the broker if there is one. This hook includes an optional lock system, allowing a passkey to be set to gate the "HOOK ON" functionality. The primary function of this hook is triggered when a payment is sent to the account where it is installed. Upon activation, the hook checks a ruleset, mints a URI token, and sends it to the payee's account. The URI tokens are minted in the order they are numbered with the NUM param. Upon completion of the URI token mint the assocated URI and NUM key are deleted from hook state. 

## Lock Feature

The lock feature demonstrates Xahau Hooks' unique ability to gate incoming transactions. It works by allowing the hook owner to set a six-digit passcode. If the passcode is not submitted with the payment as a parameter, and the lock has been enabled by the hook owner, the hook will reject the payment. This feature is particularly useful for commercial implementations that require gating asset distribution to qualified investors or buyers.

## Adding URIs

It's key that all your URIs have the same character count, or the hook will break. Test adding and minting on the testnet before using this hook on the mainnet. Xahau is very specific about predicting the sizes of data passed around. It's suggested that your metadata files for the URIs be available at one base URI, like a folder on IPFS. See the example of how I achieved a consistent character count across URIs.

- ipfs://bafybeieoyz3sghr27ybimhssgahaba5of6anmldjjtmufsxen22gmenjl4/00000**1**.json
- ipfs://bafybeieoyz3sghr27ybimhssgahaba5of6anmldjjtmufsxen22gmenjl4/00000**2**.json
- ipfs://bafybeieoyz3sghr27ybimhssgahaba5of6anmldjjtmufsxen22gmenjl4/00000**3**.json
- ipfs://bafybeieoyz3sghr27ybimhssgahaba5of6anmldjjtmufsxen22gmenjl4/00000**4**.json

## Hook Parmeters
To add and remove state for this hook you will use ```TTINVOKE``` transactions on the account with the parameter you intend to set. You can track your hook state at [XRPLWin Hook Testnet](https://xahau-testnet.xrplwin.com/):

|PARAM|NUMBER|  
|-----------|-------|  
|**URIL:**|The length in bytes of your base URI after it hex / 2 + 1. Use the XRPL Hex Visualizer Tool to convert your URIL to a uint64 before use in hook params. This needs to be set before adding the base URI. This can be updated as needed. Beware, if the URIL is not the correct URI length, your state saves and subsequent mints will fail. You can catch this by looking at your state with XRPL WIN Hook Tracking Tools and ensuring a consistent entry pattern.|  
|**URI:**|The URI pointer to your metadata. Use the XRPL Hex Visualizer Tool to convert your URI to a hex string before use in hook params. This needs to be set at the same time as the NUM param. This can be updated by re-entering the URI with the same NUM key to reset it.|  
|**NUM:**|The number of your specific URI metadata for entry. Use the XRPL Hex Visualizer Tool to convert your name/number to uint64 before use in hook params. Name/number your files 000001, 000002, 000003... and so on; that way, the counter in the hook can file and mint them in order. They can be updated after being added. A small handful of numbers are already allocated for use in this hook's functions. Do not use 999999-999991 for URI token NUMs.|  
|**COST:**|How much XAH you want to charge for a URI emission. Use the XRPL Hex Visualizer Tool to convert your COST number to a uint64 before use in hook params. This needs to be set before adding URI number keys. This can be updated as needed.|  
|**LOCK:**|A numerical passkey. If this param is set, hook users will have to submit the PASS param to unlock and use the hook's functionality. Use the XRPL Hex Visualizer to convert your LOCK number to a uint64 before use in hook params. This can be updated as needed.|  
|**COUNT:**|An optional param to adjust the hook's counter state. This param does not need to be used in most cases; the hook will keep count when adding and removing state. If you reset a certain piece of state or deal with hook errors, there is a chance your counter has gone out of sync. Ensure the COUNT param is set to the total number of URIs in your hook state. You can see the counter in the XRPL WIN Hook Tracking Tools.|  
|**PASS:**|A numerical passkey. If a hook is locked, this param must be submitted as a param with a payment transaction to unlock it. Use the [XRPL Hex Visualizer](https://transia-rnd.github.io/xrpl-hex-visualizer/) to convert your PASS number to a uint64 before use in hook params.|  
|**BROKER:**|An optional field for a Xahau broker to handle all your URI token transactions and royalties. Use the XRPL Hex Visualizer Tool to convert your Xahau address to its hexed version before use in the hook params.|  
|**ROYALTIES:**|The % amount you want to charge for royalties. This needs to be a number 1-99 for the percentage you want to charge. Decimals are not allowed in this build. Use the XRPL Hex Visualizer Tool to convert your number to a uint64.|  
|**DEL**|List the number of the hook state you want to delete.|  

## Hook State Number Keys
These are the number keys to param data stored in hook state. When debuging and looking at your hook state and namespace you will see these keys holding you data. Your not intented to enter these key number with the exception of the NUM with the URI entry.
|STATE|NUMBER|HEX|
|-----------|-------|------|
|URIL|999999|00000000000F423F|
|URI & NUM|000001-999990| 0000000000000001 - 00000000000F4236|
|COST|999997| 00000000000F423D|
|LOCK|999996| 00000000000F423C|
|COUNT|999995| 00000000000F423B|
|ROY|ROYALTY| 00000000000F423B|



## Tools

 [Xahau Docs](https://docs.xahau.network/technical/hooks-c-functions)

 [XRPLWin Hook Testnet](https://xahau-testnet.xrplwin.com/)

 [XRPL Hex Visualizer](https://transia-rnd.github.io/xrpl-hex-visualizer/) 

 [XRPLWin Hook Install Tool](https://xahau-testnet.xrplwin.com/tools/hook/from-hash)

 [Richard's Hook On Calc](https://richardah.github.io/xrpl-hookon-calculator/)

 ## Examples

**Example:** of params before hexing

- URIL: 77
- COST: 05
- LOCK: 589589
- URI: ipfs://bafybeieoyz3sghr27ybimhssgahaba5of6anmldjjtmufsxen22gmenjl4/2534.json
- NUM: 01
- DEL: 01


 **Example:** of params to add after they have been hexxed. Number to unit64 and URI to string. (HINT: when using the hook builder you dont HEX the param names only the input feilds)
 
- 5552494C: 000000000000004D
- 434F5354: 0000000000000001
- 4C4F434B: 353839353839
- 555249: 697066733A2F2F62616679626569656F797A337367687232377962696D687373676168616261356F6636616E6D6C646A6A746D75667378656E3232676D656E6A6C342F323533342E6A736F6E
- 4E554D: 0000000000000001
- 44454C: 0000000000000001


 **Example:** On chain submission adding the URI and its NUM. (HINT: you must add the URIL before adding any URIs. Having the correct URI lenght setting is imperative.)
```
    const prepared = {
      TransactionType: "Invoke",
      Account: your_account_address,
      Flags: 0,
      HookParameters: [
        {
          HookParameter: {
            HookParameterName: "555249",
            HookParameterValue: 
"697066733A2F2F62616679626569656F797A337367687232377962696D687373676168616261356F6636616E6D6C646A6A746D75667378656E3232676D656E6A6C342F323533342E6A736F6E",
          },
        },
        {
          HookParameter: {
            HookParameterName: "4E554D",
            HookParameterValue: "0000000000000001",
          },
        },
      ],
      ...networkInfo.txValues,
    };
```

## How to install the URI Token Remit Hook?

The Hookhash is AC77D68A99C6433CC9507FA9D6FCD32FBF4DB1EDF757EB73950606FE08CF269E

1. You can do it with the tool at [XRPLWin Hook Install Tool](https://xahau-testnet.xrplwin.com/tools/hook/from-hash)

2. Or you can do it sending the transaction below:

Set the hook to activate (HookOn) is when a Invoke, Payment and URIToken_Buy transaction happens. You can verify iyour HookOn value (0xfffffffffffffffffffffffffffffffffffffff7ffffffffffffffffffbffffe) in this website: [Richards Hook On Calc](https://richardah.github.io/xrpl-hookon-calculator/)

    const prepared = {
      "TransactionType": "SetHook",
      "Account": your_account_address,
      "Flags": 0,
      "Hooks": [
        {
          "Hook": {
            "HookHash": "AC77D68A99C6433CC9507FA9D6FCD32FBF4DB1EDF757EB73950606FE08CF269E",
            "HookNamespace": "0204DAD98F5ADB07B8CB073BFBCC1B331A2589ED7744C644577A024E0D98A220",
            "HookOn": "0xfffffffffffffffffffffffffffffffffffffff7ffffffffffffffffffbffffe",
          }
        }
      ],
      ...networkInfo.txValues,
    };

## How to uninstall the URI Token Remit Hook on Mainnet/Testnet?

    const prepared = {
      "TransactionType": "SetHook",
      "Account": your_account_address,
      "Flags": 0,
      Hooks:
    [        
        {                        
            Hook: {
                CreateCode: "",
                Flags: 1,
            }
        }
    ],
      ...networkInfo.txValues,
    };




## How to install the URI Token Remit Hook on Mainnet?

Same as Testnet but changing the hookhash. The Hookhash is AC77D68A99C6433CC9507FA9D6FCD32FBF4DB1EDF757EB73950606FE08CF269E.

1. You can do it by [XRPLWin Hook Install Tool](https://xahau.xrplwin.com/tools/hook/from-hash)

2. Or you can do it sending the transaction below:

```
    const prepared = {
      "TransactionType": "SetHook",
      "Account": your_account_address,
      "Flags": 0,
      "Hooks": [
        {
          "Hook": {
            "HookHash": "AC77D68A99C6433CC9507FA9D6FCD32FBF4DB1EDF757EB73950606FE08CF269E",
            "HookNamespace": "0204DAD98F5ADB07B8CB073BFBCC1B331A2589ED7744C644577A024E0D98A220",
            "HookOn": "0xfffffffffffffffffffffffffffffffffffffff7ffffffffffffffffffbffffe",
          }
        }
      ],
      ...networkInfo.txValues,
    };
```


## Current NFT Metadata and Roytlies

This hook is compliant with the Royties and brokerage standard [XLS-53d standard](https://github.com/XRPLF/XRPL-Standards/discussions/148). Setting a Royalty param on this hook will ensure a broker can be prepared to read pay it accordingly. Beware a broker controls the trade of your asset and may charge fees.

## Promosed NFT Metadata and Roytlies

I propose we write a hook that, upon URI token purchase, reads the issuer's hook state, ensures the fee is paid, and completes the NFT transfer. Once installed, the hook could also block any outgoing transactions to non-royalties hook accounts. Any minting app could prevent a transaction if the user does not have the royalties hook. This hook would have very basic code and be lightweight on users' accounts and the network. This proposed royalty standard would be compatible with XLS-53 and the URI Token Remit hook. Brokers and a royalties hook could coexist.


## Collaberation 

I want to see this hook used and upgraded. We are offering advice on Hook install and in some cases building a custom impelentation of this hook. If you would like to register assets for sale at a Xahau address reach out to Cody on X @Cbot_XRPL.


## Disclainmer

This hook is stable and user-friendly with a lot of catches, error messages, and notes. With that being said, this hook was written for the Xahau Hackathon on a timeframe and is still in an experimental state. I know there are many ways to clean up and improve this hook. There are several upgrades that will eventually be edited into the code. If you find any major vulnerabilities, please reach out to me ASAP so I can patch them. Cbot Labs INC. and specifically Cody, the author of this code, do not accept any liability for the use of this hook. Use this hook at your own expense. Anyone using this hook should do so on testnet until they fully understand its function.


## Final Thoughts

Created by [@cbot_xrpl](https://x.com/cbot_xrpl). You can find more of my projects on [cbotlabs.com](https://www.cbotlabs.com). Speical thanks to [@ekiserrepe](https://x.com/ekiserrepe) for insperation with the forwarder hook and [@angell_denis](https://x.com/angell_denis) for getting me started with C. Thank you to all of the Xahau commuinty for giving me welcoming place to build and learn !!
