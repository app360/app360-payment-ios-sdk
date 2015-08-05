//
//  Constant.h
//  App360Payment
//
//  Created by Tuan Tran Manh on 7/27/15.
//  Copyright (c) 2015 MOG. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <App360SDK/MOGConstants.h>

@class MOGSMSResponseObject;
@class MOGCardResponseObject;
@class MOGBankingResponseObject;
@class MOGPaymentResponseObject;

/*!
 `MOGSMSAmount` enum specifies different supported value of sms amount.
 */
typedef NS_OPTIONS(NSInteger, MOGSMSAmount) {
    /*!
     Amount with value 500 VND
     */
    MOGSMSAmount500   = 1 << 0,
    /*!
     Amount with value 1000 VND
     */
    MOGSMSAmount1000  = 1 << 1,
    /*!
     Amount with value 2000 VND
     */
    MOGSMSAmount2000  = 1 << 2,
    /*!
     Amount with value 3000 VND
     */
    MOGSMSAmount3000  = 1 << 3,
    /*!
     Amount with value 4000 VND
     */
    MOGSMSAmount4000  = 1 << 4,
    /*!
     Amount with value 5000 VND
     */
    MOGSMSAmount5000  = 1 << 5,
    /*!
     Amount with value 10000 VND
     */
    MOGSMSAmount10000 = 1 << 6,
    /*!
     Amount with value 15000 VND
     */
    MOGSMSAmount15000 = 1 << 7,
    /*!
     Amount that contains all values above
     */
    MOGSMSAmountAll   = MOGSMSAmount500   |
    MOGSMSAmount1000  |
    MOGSMSAmount2000  |
    MOGSMSAmount3000  |
    MOGSMSAmount4000  |
    MOGSMSAmount5000  |
    MOGSMSAmount10000 |
    MOGSMSAmount15000
};

/*!
 `MOGVendor` enum specifies different supported vendor of card transaction.
 */
typedef NS_ENUM(uint8_t, MOGVendor) {
    /*!
     Vinaphone
     */
    MOGVendorVinaphone = 0,
    /*!
     Mobifone
     */
    MOGVendorMobifone = 1,
    /*!
     Viettel
     */
    MOGVendorViettel = 2
};

/*!
 `MOGTransactionStatus` enum specifies different status of transaction.
 */
typedef NS_ENUM(uint8_t, MOGTransactionStatus) {
    /*!
     The transaction received but has not processed
     */
    MOGTransactionStatusBegin = 0,
    /*!
     The transaction received and is being processed
     */
    MOGTransactionStatusPending = 1,
    /*!
     The transaction is processed completly
     */
    MOGTransactionStatusCompleted = 2,
    /*!
     The transaction is failed
     */
    MOGTransactionStatusFailed = 3,
    /*!
     The transaction status is undefine
     */
    MOGTransactionStatusUndefine = 4,
};

/*!
 `MOGTransactionType` enum specifies different type of transaction.
 */
typedef NS_ENUM(uint8_t, MOGTransactionType) {
    /*!
     Make transaction via SMS
     */
    MOGTransactionTypeSMS = 0,
    /*!
     Make transaction via phone card
     */
    MOGTransactionTypeCard = 1,
    /*!
     Make transaction via E-Banking
     */
    MOGTransactionTypeBank = 2
};

/*!
 `MOGAPICode` enum specifies status code of API response.
 */
typedef NS_ENUM(uint8_t, MOGAPICode) {
    /*!
     Make transaction via SMS
     */
    MOGAPICodeSuccess = 0,
    /*!
     Make transaction via phone card
     */
    MOGAPICodeError = 1
};

///--------------------------------------
/// @name Vendor name
///--------------------------------------

/*! @abstract vinaphone */
extern NSString *const kMOGVendorVinaphone;

/*! @abstract mobifone */
extern NSString *const kMOGVendorMobifone;

/*! @abstract viettel */
extern NSString *const kMOGVendorViettel;

/*! @abstract gate */
extern NSString *const kMOGVendorGate;

/*! @abstract vcoin */
extern NSString *const kMOGVendorVcoin;

/*! @abstract zing */
extern NSString *const kMOGVendorZing;

/*! @abstract bit */
extern NSString *const kMOGVendorBit;

///--------------------------------------
/// @name Blocks
///--------------------------------------

/*! @abstract SMS charging response block. Return SMS response if success. If not,return with error */
typedef void (^MOGSMSResponseBlock)(MOGSMSResponseObject *responseObject, NSError *error);

/*! @abstract Phone card charging response block. Return phone card response if success. If not,return with error */
typedef void (^MOGCardResponseBlock)(MOGCardResponseObject *responseObject, NSError *error);

/*! @abstract E-banking charging response block. Return e-banking response if success. If not,return with error */
typedef void (^MOGBankingResponseBlock)(MOGBankingResponseObject *responseObject, NSError *error);

/*! @abstract payment response block. Return payment response if success. If not,return with error */
typedef void (^MOGPaymentResponseBlock)(MOGPaymentResponseObject *responseObject, NSError *error);

///--------------------------------------
/// @name Errors
///--------------------------------------

/*! @abstract 107: Vendor name is invalid. */
extern NSInteger const kMOGErrorVendorNameInvalid;

/*! @abstract 108: Amount value is invalid. */
extern NSInteger const kMOGErrorAmountInvalid;

/*! @abstract 109: Card transtion is failed. */
extern NSInteger const kMOGErrorCardChargingFailed;

/*! @abstract 110: User cancel send SMS dialog. */
extern NSInteger const kMOGErrorUserCancelSMSDialog;

/*! @abstract 111: Send SMS failed. */
extern NSInteger const kMOGErrorSendSMSFailed;

/*! @abstract 112: Get SMS syntax failed. */
extern NSInteger const kMOGErrorGetSMSSyntax;

/*! @abstract 113: Check transaction status failed. */
extern NSInteger const kMOGErrorCheckTransactionStatusFailed;
