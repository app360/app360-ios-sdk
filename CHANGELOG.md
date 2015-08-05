##Version 1.5.0

**Release date**: 18 Jun 2015
 - **[CHANGED]** Separate Payment and App360SDK. To use Payment API, you must import it separatly
 - **[DEPRECATE]** Deprecated `initializeWithApplicationId:clientKey:block` in `App360SDK`
 - **[ADDED]** Add `initializeWithApplicationId:clientKey` method in `App360SDK`

##Version 1.4.0

**Release date**: 18 Jun 2015
 - **[CHANGED]** Separate Payment UI and Payment Request API
 - **[DEPRECATE]** Deprecated `getSMSSyntaxWithSMSAmount` in `MOGPaymentSDK`
 - **[ADDED]** Add `requestSMSSyntaxWithAmount` in `MOGPaymentSDK`
 - **[DEPRECATE]** Deprecated `makePhoneCardTransactionWithVendor` in `MOGPaymentSDK`
 - **[ADDED]** Add `makeCardTransactionWithVendor` in `MOGPaymentSDK`

##Version 1.2.0

**Release date**: 31 Mar 2015

 - **[CHANGED]** Rename `m360.plist` to `app360.plist`

##Version 1.1.0

**Release date**: 10 Feb 2015

 - **[DELETE]** `MOGAmount` enum
 - **[DELETE]** `+getSMSSyntaxWithAmount:block:`
 - **[DELETE]** `+getSMSSyntaxWithAmount:payload:block:`
 - **[DELETE]** `+makePhoneCardTransactionWithVendor:cardCode:cardSerial:block:`
 - **[DELETE]** `+makeBankingTransactionWithAmount:block:`
 - **[ADD]** `MOGSMSAmount` enum
 - **[ADD]** `+getSMSSyntaxWithSMSAmount:payload:block:`
 - **[ADD]** `+makeSMSTransactionWithDelegate:datasource:payload:`
 - **[ADD]** `+makePhoneCardTransactionWithDelegate:datasource:payload:`
 - **[ADD]** `+makeBankingTransactionWithDelegate:datasource:payload:`
 - **[ADD]** `+makeTransactionWithPayload:`

##Version 1.0.0

**Release date**: 29 Jan 2015

 - Initialization version support charging via phone card, SMS and e-banking
 - Support checking transaction status