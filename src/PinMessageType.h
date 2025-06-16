#pragma once

enum class PinMessageType {
    CardReadSuccess,
    CardReadFailure,
    PromptPinEntry,
    PinSuccess,
    PinFailure,
    PinNotSet
};
