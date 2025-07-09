#pragma once

enum class OutputType {
    WelcomeMessage,
    CardReadSuccess,
    CardReadFailure,
    PromptPinEntry,
    PromptUserConfirmation,
    PinEntryCanceled,
    InvalidConfirmation,
    PinSuccess,
    SelectOperation,
    PinFailure,
    MaximumRetriesExceeded,
    AccessDenied,
    PinNotSet,
    PromptPinSetup,
    PromptPinConfirmation,
    PinSetupSuccess,
    PinSetupFailure,
    PinMismatch,

    OperationMenu,
    PromptWithdrawInput,
    PromptDepositInput,
    WithdrawSuccess,
    WithdrawFailure,
    DepositSuccess,
    DepositFailure,
    DisplayBalance,
    InvalidSelection
};
