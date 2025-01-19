

## URI Token Mint Hook for Xahau Network


This C hook is desgined to automasly distribute RWA (real world asssts) or NFTs based on the Xahau hook rule engine. rental contracts and digital art are some basic example of the use of this hook. This hook is ideal for use by real estate transactions or even by digital products.

## What Does This Hook do

The hook is installed on an account. URI's can then be added/removed from the hook state via an invoke transactions. The hook primary fuction is activated when a payment is sent to the account it is installed on. the hook will check a ruleset, mint a URI token, and send it to payees account.

## Tools

 [XRPLWin Hook Install Tool](https://xahau-testnet.xrplwin.com/tools/hook/from-hash)

 [XRPLWin Hook Testnet](https://xahau-testnet.xrplwin.com/account/)

 [Xahau Docs](https://docs.xahau.network/technical/hooks-c-functions)

 [Richard's Hook On Calc](https://richardah.github.io/xrpl-hookon-calculator/)



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

## How to add an URI?

The hook allows up to 10 addresses to which the amounts received can be distributed in equal parts. They will be registered with an identifier from 00 to 09. The addresses must be converted to Account ID. To do this you can use the following services:

- https://hooks.services/tools/raddress-to-accountid 
- https://transia-rnd.github.io/xrpl-hex-visualizer

To check if you are doing it right, address: rBnGX5KRERL2vMtZU2hDpF4osbhvichmvn will be translated to 6E7FE292948037180F3646CC248FAF2BCACD59893C

**Visual representation of the namespace or address book:**

|identifier|address|
|-----------|-------|
|01|address1 translated to AccountID|
|02|address2 translated to AccountID|
|03|address3 translated to AccountID|
|..|..                              |
|09|address9 translated to AccountID|

To add an account we must create an Invoke transaction from the hook account and add the following Hook parameters and values:

ADD with the AccountID
NUM with the position we want between 00 to 09

**Example:**

- ADD: D53F733E54B866B9FBDB85762071832B03A56C76
- NUM: 00

We need to change ADD and NUM keywords to hex. ADD = 414444 and NUM = 4E554D.
Also, we need to translate address account rLSYATPWj9UECGBEeVpxwEN16CuEREK3uR to AccountID D53F733E54B866B9FBDB85762071832B03A56C76

- 414444: D53F733E54B866B9FBDB85762071832B03A56C76
- 4E554D: 00

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
## Video Tutorial

The user @[ainittomai](https://www.x.com/ainittomai) has created a video tutorial to learn how to use this hook on Xahau Testnet: [https://www.youtube.com/watch?v=rf8zSmrZkPA](https://www.youtube.com/watch?v=rf8zSmrZkPA)

## Last Thoughts

Created by @[ekiserrepe](https://x.com/ekiserrepe). You can find more of my projects on [ekiserrepe.com](https://www.ekiserrepe.com)
