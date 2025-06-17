#pragma once

enum class PinMessageType {
    WelcomeMessage,
    CardReadSuccess,
    CardReadFailure,
    PromptPinEntry,
    PromptUerConfirmation,
    PinEntryCanceled,
    InvalidConfirmation,
    PinSuccess,
    SelectOperation,
    PinFailure,
    MaximumRetriesExceeded,
    AccessDenied,
    PinNotSet
};
