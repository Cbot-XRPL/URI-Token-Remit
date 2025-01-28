

## URI Token Mint Hook for Xahau Network


This hook is designed to automatically distribute URI Tokens (RWA or NFT) based on the Xahau hook rule engine. This hook could potentially replace a transfer agent, allowing users a secure way to get assets without a broker. This hook will essentially allow you to register unique assets for distribution at a Xahau address. Some potential assets that could be distributed based on this hook are art, real estate, tickets, and digital products. You can find our Xahau Art Vault example of this hook on Mainnet at [address] and our Concert Rental Tickets on testnet installed at [address]

## What Does This Hook do

The hook is installed on an account. The length of your URIs (in bytes) set through a parameter called URIL. URIs and their NUM can be added or removed from the hook state via invoke transactions. It is crucial that all URIs have the exact same length, as this consistency is key to the hook's functionality (more details on this below). You must also specify the cost to charge users for minting a URI token. This hook includes an optional lock system, allowing a passkey to be set to gate the "HOOK ON" functionality. The primary function of this hook is triggered when a payment is sent to the account where it is installed. Upon activation, the hook checks a ruleset, mints a URI token, and sends it to the payee's account. The URI tokens are minted in the order they are numbered with the NUM param. Upon completion of the URI token mint the assocated URI and NUM key are deleted from hook state. 

## Lock Feature

The lock feature demonstrates Xahau Hooks' unique ability to gate incoming transactions. It works by allowing the hook owner to set a six-digit passcode. If the passcode is not submitted with the payment as a parameter and the lock has been enabled by the hook owner, the hook will reject the payment. This feature is particularly useful for commercial implementations that require gating asset distribution to qualified investors or buyers.

## Adding URIs

Its key all your URIs have the same Charater count or the hook will break. Test adding and minting on testnet before using this hook on mainnet. Xahau is very specfic about predicting sizes of data passed around. Its sujested your metadata files for the URIs to be available at one base URI like a folder on IPFS. See the example of how I achived a consitant char count accross URIS.

- ipfs://bafybeieoyz3sghr27ybimhssgahaba5of6anmldjjtmufsxen22gmenjl4/00000**1**.json
- ipfs://bafybeieoyz3sghr27ybimhssgahaba5of6anmldjjtmufsxen22gmenjl4/00000**2**.json
- ipfs://bafybeieoyz3sghr27ybimhssgahaba5of6anmldjjtmufsxen22gmenjl4/00000**3**.json
- ipfs://bafybeieoyz3sghr27ybimhssgahaba5of6anmldjjtmufsxen22gmenjl4/00000**4**.json

## Hook Parmeters
To add and remove state for this hook you will use ```TTINVOKE``` transactions on the account with the parameter you intend to set. You can track your hook state at [XRPLWin Hook Testnet](https://xahau-testnet.xrplwin.com/):

|PARAM|NUMBER|
|-----------|-------|
|**URIL:**|The lenght in bytes of your base URI after it hex / 2 + 1 . Use the XRPL Hex Visualizer Tool to convert your URIL to a unit64 before use in hook params. This needs to set before adding the base URI. This can be updated as needed. Beware if the URIL is not correct URI lenght your state saves and subsiquent mints will fail. You can catch this by looking at you state with XRPL WIN Hook Tracking Tools and ensure a consitant entry pattern.
|**URI:**|The URI pointer to your metadat. Use the XRPL Hex Visualizer Tool to convert your URI to a hex string before use in hook params. This needs to set at the same time as the NUM param. This can be updated by re-entering the URI with the same NUM key to reset it|
|**NUM:**|The number of your spefic URI metadata for entry. Use the XRPL Hex Visualizer Tool to convert your name/number to unit64 before use in hook params. Name/number your files 000001, 000002, 000003 .. and so on, that way the counter in the hook can file and mint them in order. They can be updated after being added. A small handful of numbers are already allocated for use in this hook functions. Do not use 999999-999991 for URI token NUMs.|
|**COST:**|How Much XAH you want to charge for a URI emisson. Use the XRPL Hex Visualizer Tool to convert your COST number to a unit64 before use in hook params. This needs to set before adding URI number keys. This can be updated as needed.|
|**LOCK:**|A numerical passkey. If this param is set hook users will have to submit the PASS param to unlock and use the hooks fuctionality. Use the XRPL Hex Visualizer to convert your LOCK number to a unit64 before use in hook params. This can be updated as needed.|
**COUNT:**|A optional param to adjsut the hooks counter state. This param does not need to be used in most cases the hook will keep count when adding and removing state. If you reset a certain peice of state or deal with hook errors there is a chance your counter has gone out of sync. Ensure the COUNT param is set to the total number of URIs in your hook state. You can see the counter in the  XRPL WIN Hook Tracking Tools
|**PASS:**|A numerical passkey. If a hook is locked this param must be submited as a param with a payment transaction to unlock it. Use the [XRPL Hex Visualizer](https://transia-rnd.github.io/xrpl-hex-visualizer/) to convert your PASS number to a unit64 before use in hook params.|
|**DEL**| List the number of the hook state you want to delete.|

## Hook State Number Keys
These are the number keys to param data stored in hook state. When debuging and looking at your hook state and namespace you will see these keys holding you data. Your not intented to enter these key number with the exception of the NUM with the URI entry.
|STATE|NUMBER|HEX|
|-----------|-------|------|
|URIL|999999|00000000000F423F|
|URI & NUM|000001-999990| 0000000000000001 - 00000000000F4236|
|COST|999997| 00000000000F423D|
|LOCK|999996| 00000000000F423C|
|COUNT|999995| 00000000000F423B|


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
            HookParameterName: "414444",
            HookParameterValue: "D53F733E54B866B9FBDB85762071832B03A56C76",
          },
        },
        {
          HookParameter: {
            HookParameterName: "4E554D",
            HookParameterValue: "00",
          },
        },
      ],
      ...networkInfo.txValues,
    };
```

## How to install the URI Token Remit Hook?

The Hookhash is 1A9D1EEA98A9BE3C45A35872E51E36B6E73CBB7033A96CE0D98DB484215E0494

1. You can do it with the tool at [XRPLWin Hook Install Tool](https://xahau-testnet.xrplwin.com/tools/hook/from-hash)

2. Or you can do it sending the transaction below:

Set the hook to activate (HookOn) is when a Invoke, Payment and URIToken_Buy transaction happens. You can verify iyour HookOn value (FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF7FFFFFFFFFFFF7FFFFFBFFFFE) in this website: [Richards Hook On Calc](https://richardah.github.io/xrpl-hookon-calculator/)

    const prepared = {
      "TransactionType": "SetHook",
      "Account": your_account_address,
      "Flags": 0,
      "Hooks": [
        {
          "Hook": {
            "HookHash": "1A9D1EEA98A9BE3C45A35872E51E36B6E73CBB7033A96CE0D98DB484215E0494",
            "HookNamespace": "0000000000000000000000000000000000000000000000000000000000000000",
            "HookOn": "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF7FFFFFFFFFFFF7FFFFFBFFFFE",
          }
        }
      ],
      ...networkInfo.txValues,
    };

## How to uninstall the Forwarder Hook on Mainnet/Testnet?

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




## How to install the Forwarder Hook on Mainnet?

Same as Testnet but changing the hookhash. The Hookhash is D22582E8BAF59FC682DEF490A3992CADB3CD5CCE851FB358B2DE299ABE30DB9E.

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
            "HookHash": "D22582E8BAF59FC682DEF490A3992CADB3CD5CCE851FB358B2DE299ABE30DB9E",
            "HookNamespace": "0000000000000000000000000000000000000000000000000000000000000000",
            "HookOn": "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF7FFFFFFFFFFFF7FFFFFBFFFFE",
          }
        }
      ],
      ...networkInfo.txValues,
    };
```


## NFT Metadata and Roytlies

I propose everyone include there roytlie amount in out NFT metadata. We can then write a hook that on URI token purchase, the metadata is read, fee paid, and NFt transfer finished. If you have the hook installed it could also block anyout going TX to non royties hook accounts. This would allow for a consistant hook to be install on all nft users account. This proposed roytie standard would be compadible with URI Token Remit hook.

## Collaberation 

I want to see this hook used and upgraded. If you would like to register assets for sale at a Xahau address reach out to Cody on X @Cbot_XRPL. We are offering advice on Hook install and in some cases building a custom impelentation of this hook.


## Disclainmer

This hook is stable and user freindly with alot of catchs, error messages, and notes. With that being said this hook was written for the Xahau Hackaton on a timeframe. I know there is many ways to clean up and improve this hook. There is serval upgrades that will eventully be edited into the code. If you find any major vulnerabilities please reach out to me asap so I can patch them. Cbot Labs INC. and specially Cody the author of this code do not acccpt any liablty for the use of this hook. Use this hook at your own expence. Anyone using this hook should do so on testnet until they fully understand its fuction.


## Last Thoughts

Created by [@cbot_xrpl](https://x.com/cbot_xrpl). You can find more of my projects on [cbotlabs.com](https://www.cbotlabs.com). Speical thanks to [@ekiserrepe](https://x.com/ekiserrepe) for insperation with the forwarder hook and [@angell_denis](https://x.com/angell_denis) for getting me started with C. Thank you to all of the Xahau commuinty for giving me welcoming place to build and learn !!
