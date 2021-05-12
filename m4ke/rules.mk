# MCU name
MCU = atmega32u4

# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   ATmega32A    bootloadHID
#   ATmega328P   USBasp
BOOTLOADER = caterina

# Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically

MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
UNICODE_ENABLE = yes        # Unicode
TAP_DANCE_ENABLE = yes      # Double press does something different
ENCODER_ENABLE = yes		# Enable rotary encoders
LTO_ENABLE = yes			# Reduce firmware size
KEY_LOCK_ENABLE = yes		