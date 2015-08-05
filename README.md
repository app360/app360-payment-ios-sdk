#Introduction

App360 Payment SDK is a part of App360 Platform, it provides easiest way to integrate payment service (including sms, phone card and e-banking) into your application.

The App360 Payment iOS SDK supports iOS version 6.0 and above.

#Requirements

##Development Environment

| App360SDK Version | Minimum iOS Target | 				Notes 			|
|:-----------------:|:------------------:|:----------------------------:|
|1.5.0|6.0|Xcode 6.1 is required. Support armv7, armv7s and arm64 architectures (+ i386 for the simulator)|

###Library compatibility

The App360 iOS SDK supports all iOS 6.0 and above versions. It compiles against the armv7, armv7s and arm64 architectures (+ i386 for the simulator).

###Xcode

We are using Xcode 6.4 to create our demo projects. You may encounter some errors if you are using a lower version of Xcode. That's why we recommend you work on the latest (non-beta) available version.

###App360

App360 Payment SDK use appscoped-id session of App360SDK to make payment. So, you must integrate with App360SDK first in order to call any payment API.

#Getting started with Demo project

Firstly, clone or download this repository to your machine.

- `git clone https://github.com/app360/app360-payment-ios-sdk.git`
- Or, download from https://github.com/app360/app360-ios-sdk/releases

Open AppDelegate.m inside demo project, find `initializeWithApplicationId` line and replace the placeholders with your application credentials.

Run the project. The app demonstrates capability of App360 SDK, including app-scoped ID and payment.

# 3 Step to integrate with App360SDK

## 1. Integrate with App360SDK

The first thing you need to do is integrate your game/app with App360SDK. For more information, please read [App360SDK document](https://github.com/app360/app360-ios-sdk) to know how to do that.

## 2. Download Payment SDK

There are multiple ways to include the App360 Payment SDK into an Xcode project. We can use CocoaPods, manually include the framework and its dependencies

> ### Cocoapod (Coming soon)
> CocoaPods is the fastest way to get up and running with App360 in your iOS app. Just add the following to your Podfile, pod install, and skip to Getting started in Xcode
> ```
pod 'App360-Payment-SDK', '>= 1.5.0'
```
> ### Download App360-Payment-SDK
> Download the iOS SDK from the this repo, unzip the App360 Payment SDK file, drag the .framework folder to your XCode project under Frameworks

## 3. Integrate with Payment SDK

### 3.1. Payment flow

Before going to integrate with any API, you should look and know about payment flow of App360 Platform.

In order to secure payment flow, your application might choose to integrate with our SDK on both client-side and server-side, in which case the payment flow is depict in the following diagram:

![Payment flow](http://www.websequencediagrams.com/cgi-bin/cdraw?lz=dGl0bGUgUGF5bWVudCBzZXF1ZW5jZQoKR2FtZS0-U0RLOgAUCXJlcXVlc3QgKDEpClNESy0-R2FtZTogVHJhbnNhY3Rpb24gaWQsIHN0YXR1cywgYW1vdW50ICgyKQBGB0dhbWUgc2VydmVyOiBzZW5kIHQAMAtkYXRhIGZvciBpbnNwZQBJBigzAF8LADIJACoMaWQAYQgsIHVzZXJfaWQgKDQAbAYAZQcAgT8HYWNrIChIVFRQAIEaByAyMDApICg1AB0PAIEYDWNvbmZpcm0gKDYAExMAFAs3KQ&s=rose)

1. The application (client-side) calls payment API from the SDK, optionally with a custom payload (documented below).
2. The SDK returns transaction id and other details (if available)
3. The application client sends transaction data to its server awaiting confirmation
4. SDK server calls a pre-registered endpoint of the application server to notify about transaction status when it completes
    - Note that there is no guarantee about the order of (3) and (4) (i.e. (4) may happen before (3))
5. Application server acknowledges SDK server's call by responding with HTTP status code 200.
6. Application server validates the transaction based on the information it has (transaction ID, payload, etc.)
7. Application server confirms/notifies game client about the status of the transaction

**Note**:
- To register your application's server endpoint, go to https://developers.app360.vn/; set _Payment callback endpoint_ in application details page, _Information_ tab.
- Before using any payment methods, the application must first initialize the SDK. See section _SDK Initialization_ above.

### 3.2. Making SMS transaction

To make a sms transaction, client must call SDK API to request make transaction. After received request, SDK will call to SDK's server and return a list of available sms syntax. Client open send sms dialog to guide user make transaction with information is provided.

```objective-c
//Set payload string. The addition infomation you want to send with transaction. such as id of user make this transaction
//This payload string will send to callback URL (that configured on dashboard) when transaction finish successfully
NSString *payload = @"gamer-id";

[App360Payment requestSMSSyntaxWithAmount:@"500, 10000, 15000, 50000" vendor:kMOGVendorVinaphone payload:payload block:^(MOGSMSResponseObject *responseObject, NSError *error)
{
    if (error) {
        //API request failed
        
    } else if (responseObject.code == MOGAPICodeError){
        //API response 200 OK but something wrong
        
    } else {
        //success
        NSString *transactionId  = responseObject.transactionId;
        MOGTransactionType type = responseObject.type; //It should be MOGTransactionTypeSMS
        MOGTransactionStatus status = responseObject.status; //It should be MOGTransactionStatusBegin, means server just create transaction but not receive sms
        
        NSLog(@"SMS transaction: %@, type: %@, status: %@", transactionId, NSStringFromType(type), NSStringFromStatus(status));
        
        NSArray *services = responseObject.services;
        for (MOGSMSItem *item in services) {
            NSString *syntax = item.syntax;
            NSString *sendTo = item.recipient;
            //Syntax charging
            NSLog(@"Send %@ to %@ to make transaction", syntax, sendTo);
        }
    }
}];
```

### 3.3. Making card transaction

After user enter card (phone card or game card) information and hit a button to purchase, client call SDK API to make transaction with information above.

```Objective-C
NSString *cardCode = @"card-code";
NSString *cardSerial = @"card-serial";

//Set payload string. The addition infomation you want to send with transaction. such as id of user make this transaction
//This payload string will send to callback URL (that configured on dashboard) when transaction finish successfully
NSString *payload = @"gamer-id";

[App360Payment makeCardTransactionWithVendor:kMOGVendorGate cardCode:cardCode cardSerial:cardSerial payload:payload block:^(MOGCardResponseObject *responseObject, NSError *error)
{
    if (error) {
        //API request failed
        NSLog(@"Error: %@", error.localizedDescription);
        
    } else if (responseObject.code == MOGAPICodeError){
        //API response 200 OK but something wrong
        NSLog(@"");
    } else {
        //success
        NSString *transactionId  = responseObject.transactionId;
        MOGTransactionType type = responseObject.type; //It should be MOGTransactionTypeSMS
        MOGTransactionStatus status = responseObject.status; //It should be MOGTransactionStatusBegin, means server just create transaction but not receive sms
        
        NSLog(@"Card transaction: %@, type: %@, status: %@", transactionId, NSStringFromType(type), NSStringFromStatus(status));
    }
}];
```

### 3.4. Making e-banking transaction

To make a e-banking transaction, client must call SDK API to request make transaction. After received request, SDK will call to SDK's server and return an url. Client open a web page that load url above and guide user make transaction on it.

```Objective-C
//Set payload string. The addition infomation you want to send with transaction. such as id of user make this transaction
//This payload string will send to callback URL (that configured on dashboard) when transaction finish successfully
NSString *payload = @"gamer-id";

[App360Payment makeBankingTransactionWithAmount:50000 payload:payload block:^(MOGBankingResponseObject *responseObject, NSError *error) {
                                              
    if (error) {
      //API request failed
      
    } else if (responseObject.code == MOGAPICodeError){
      //API response 200 OK but something wrong
      NSLog(@"e-banking charging error: %@", responseObject.message);
    } else {
      //success
      NSString *transactionId  = responseObject.transactionId;
      MOGTransactionType type = responseObject.type; //It should be MOGTransactionTypeSMS
      MOGTransactionStatus status = responseObject.status; //It should be MOGTransactionStatusBegin, means server just create transaction but not receive sms
      
      //The URL of webpage use to charge this transaction.After receive this URL, you can guild user to pay via that webpage
      NSURL *chargingURL = responseObject.payURL;
      
      NSLog(@"E-banking transaction: %@, type: %@, status: %@, URL: %@", transactionId, NSStringFromType(type), NSStringFromStatus(status), chargingURL.absoluteString);
    }
}];
```

# What's next?

- Checkout [our document](http://docs.app360.vn/) for more infomation of App360SDK
- Integrate with [Payment API](http://docs.app360.vn/?page_id=271)
- If you got any trouble, checkout the [FAG page](http://docs.app360.vn/?page_id=228) or send a support request

#Support
Please contact [us](mailto:support@app360.vn) for general inquiries.

##For a technical issue
In case you have a technical issue, you can reach [our technical support team](mailto:support@app360.vn).
Please provide the following information when you reach out, it'll allow us to help you much more quickly.

 - **The library version** you're using. You can get the precise number by
   printing the result of the `[App360SDK getSDKVersion];` method.
 - **The platform** used to produce the problem (device model or simulator),
   and the iOS version.
 - **The steps** to reproduce the problem.
 - If possible, **some pieces of code**, or even a project.

> For more information, please go to https://developers.app360.vn.