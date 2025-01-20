

## URI Token Mint Hook for Xahau Network


This C hook is desgined to automasly distribute RWA (real world asssts) or NFTs based on the Xahau hook rule engine. This hook is ideal for use in real estate transactions or in the sale of digital products. You can find our Fine Art Agent example of this hook on Mainnet at address: and our Rental Contracts Rule engine on testnet installed at address:.

## What Does This Hook do

The hook is installed on an account. URI's can then be added/removed from the hook state via an invoke transactions. The hook primary HOOKON fuction is activated when a payment is sent to the account it is installed on. the hook will check a ruleset, mint a URI token, and send it to payees account.

## Tools

 [XRPLWin Hook Install Tool](https://xahau-testnet.xrplwin.com/tools/hook/from-hash)

 [XRPLWin Hook Testnet](https://xahau-testnet.xrplwin.com/account/)

 [Xahau Docs](https://docs.xahau.network/technical/hooks-c-functions)

 [Richard's Hook On Calc](https://richardah.github.io/xrpl-hookon-calculator/)


## Adding URIs

This hook is requires your metadata files for the URIs to be available at one base URI and each file name to corrspond with the number key used when adding them to the hook state. Before you can add your URIs to stage them for future minting you must set a URI or base path lenght in the hook state. the BURI lenght can be updated if need after the hook is already set and URIs are added. A good choise for a base URI is to pin your files to an IFPS folder to ensure they presist. NFTstoage will give you an api key/gateways and allow you to pin to IPFS on the site or from your command line.

### URI Parmeters

- URI: Pointer to your asset. Use the [XRPL Hex Visualizer](https://transia-rnd.github.io/xrpl-hex-visualizer/) to convert your BURI to a hex string before use in hook params.
- URIL: The lenght in bytes of the URI after it hex / 2. Use the [XRPL Hex Visualizer](https://transia-rnd.github.io/xrpl-hex-visualizer/) to convert your BURI to a unit64 before use in hook params.
- NUM: A number key in the hook for sorting. Use the [XRPL Hex Visualizer](https://transia-rnd.github.io/xrpl-hex-visualizer/) to convert your BURI to a unit64 before use in hook params.
- DEL: List the number key of the URI you want to delete

To add and remove URI staged for minting you will use ```TTINVOKE ``` transactions on the hook account with the Hook parameters:

**Example:** of params before hexing

- URI: 68747470733A2F2F746573742F
- URIL: 14
- NUM: 01

 **Example:**nof params to add after they have been hexxed

- URI: 68747470733A2F2F746573742F
- URIL: 000000000000000E
- NUM: 0000000000000001

 **Example:** on chain submisson
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
