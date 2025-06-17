#pragma once

enum class ATMState {
    Idle,
    CardRead,
    PinPrompt,
    PinConfirm,
    Validating,
    AccessGranted,
    AccessDenied,
    NoPinSet,
    Error,
    Exit
};
