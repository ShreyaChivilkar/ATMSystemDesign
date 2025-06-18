#pragma once

enum class PinMessageType {
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
    PinMismatch
};
