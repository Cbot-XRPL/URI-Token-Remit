

## URI Token Mint Hook for Xahau Network

This C hook is desgined to automasly distribute RWA or NFTs based on the Xahau hook rule engine. This hook could pontintally be use in rental transactions or in the sale of digital products. You can find our Fine Art Vault example of this hook on Mainnet at address: and our Campsite Rental Tickets on testnet installed at address:.

## What Does This Hook do

The hook is installed on an account. URI's can then be added/removed from the hook state via an invoke transactions. You can add the cost you want charge users to mint a uri token. The hook primary fuction is activated when a payment is sent to the account it is installed on. the hook will check a ruleset, mint a URI token, and send it to payees account. This hooks fetures an optional lock system that allows a paskey to set to gate the HOOK ON fuctionality.


## Tools

 [Xahau Docs](https://docs.xahau.network/technical/hooks-c-functions)

 [XRPLWin Hook Testnet](https://xahau-testnet.xrplwin.com/)

 [XRPL Hex Visualizer](https://transia-rnd.github.io/xrpl-hex-visualizer/) 

 [XRPLWin Hook Install Tool](https://xahau-testnet.xrplwin.com/tools/hook/from-hash)

 [Richard's Hook On Calc](https://richardah.github.io/xrpl-hookon-calculator/)


## Hook State Number Keys
These are the number keys to param data stored in hook state. You will learn how to interact with them in the hook parmeters section.

|STATE|NUMBER|HEX|
|-----------|-------|------|
|URI|999999|00000000000F423F|
|URIL|999998|00000000000F423E|
|COST|999997| 00000000000F423D|
|LOCK|999996| 00000000000F423C|
|NUM|000001-999990| 00000000000F4236 - 0000000000000001|




## Installing the hook



## Adding URIs

This hook is requires your metadata files for the URIs to be available at one base URI and each file name to corrspond with the number key used when adding them to the hook state. Before you can add your URIs to stage them for future minting you must set a URI or base path lenght in the hook state. the BURI lenght can be updated if need after the hook is already set and URIs are added. A good choise for a base URI is to pin your files to an IFPS folder to ensure they presist. NFTstoage will give you an api key/gateways and allow you to pin to IPFS on the site or from your command line.

## Hook Parmeters
To add and remove state for this hook you will use ```TTINVOKE ``` transactions on the account with the parameter you intend to set:

|PARAM|NUMBER|
|-----------|-------|

|**URIL:**|The lenght in bytes of your base URI after it hex / 2. Use the [XRPL Hex Visualizer](https://transia-rnd.github.io/xrpl-hex-visualizer/) to convert your URIL to a unit64 before use in hook params. This needs to set before adding URI number keys. This can be updated as needed. Stored at namespace number 999998.|
|**URI:**|The base URI pointer to your storage location. Use the [XRPL Hex Visualizer](https://transia-rnd.github.io/xrpl-hex-visualizer/) to convert your URI to a hex string before use in hook params. Stored at namespace number 999999.|
|**NUM:**|The number/name of your spefic URI metadata. Use the [XRPL Hex Visualizer](https://transia-rnd.github.io/xrpl-hex-visualizer/) to convert your name/number to unit64 before use in hook params. A small handful of numbers are already allocated to seing for this hook 999999-999991 do not hex and use numbers in this range for URIs it will disrute the use of this hook.|
|**COST:**|How Much XAH you want to charge for a URI emisson. Use the [XRPL Hex Visualizer](https://transia-rnd.github.io/xrpl-hex-visualizer/) to convert your COST number to a unit64 before use in hook params. This needs to set before adding URI number keys. This can be updated as needed. Stored at namespace number 999997.|
You can add the cost you want charge users to mint a uri token.
|**LOCK:**|A numerical passkey. If this param is set hook users will have to submit the PASS param to unlock and use the hooks fuctionality. Use the [XRPL Hex Visualizer](https://transia-rnd.github.io/xrpl-hex-visualizer/) to convert your LOCK number to a unit64 before use in hook params. This can be updated as needed. Stored at namespace number 999997.|
|**PASS:**|A numerical passkey. If a hook is locked this param must be submited as a param with you transaction to unlock it.  Use the [XRPL Hex Visualizer](https://transia-rnd.github.io/xrpl-hex-visualizer/) to convert your PASS number to a unit64 before use in hook params.|
|**DEL**| List the number of the hook state you want to delete.|


To add and remove state for this hook you will use ```TTINVOKE ``` transactions on the account with the parameter you intend to set:

**Example:** of params before hexing

- URI: 68747470733A2F2F746573742F
- URIL: 14
- NUM: 01
- DEL: 01

 **Example:** of params to add after they have been hexxed (HINT: when using the hook builder you dont HEX the param names only the feilds as descrided above)

- URI: 68747470733A2F2F746573742F
- URIL: 000000000000000E
- NUM: 0000000000000001
- DEL: 0000000000000001


 **Example:** On chain submission adding the URIL prior to adding some URI number. (HINT: when using the hook builder you dont HEX the param names only the feilds as descrided above)
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





## How to delete addresses?

To delete you have to create an Invoke transaction from the hook account and use as parameter DEL and the position between 00 to 09 as value. In case there is any address registered with that identifier, it will delete it.

DEL and the position we want to delete between 00 to 09

**Example:**

- DEL: 00

We need to translate DEL keyword to hex. 

- DEL = 44454C

Numbers from 00 to 09 stay the same. No need to translate them.

    const prepared = {
      TransactionType: "Invoke",
      Account: your_account_address,
      Flags: 0,
      HookParameters: [
        {
          HookParameter: {
            HookParameterName: "44454C",
            HookParameterValue: "00",
          }
        },
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


## Last Thoughts

Created by @[cbot_xrpl](https://x.com/cbot_xrpl). You can find more of my projects on [cbotlabs.com](https://www.cbotlabs.com)
