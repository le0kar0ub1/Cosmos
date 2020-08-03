/********************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <kernel/def/def.h>

u32_t cosmos_signature_hex = 0xC05A05;

REGISTER_COSMOS_DATA(
    signature_hex,
    &cosmos_signature_hex,
    sizeof(cosmos_signature_hex)
);

char const *cosmos_signature_char = "Cosmos";

REGISTER_COSMOS_DATA(
    signature_char,
    &cosmos_signature_char,
    sizeof(cosmos_signature_char)
);

char const *cosmos_signature_asciiart =
"\
  _____ ____   _____ __  __  ____   _____     \n\
 / ____/ __ \\ / ____|  \\/  |/ __ \\ / ____| \n\
| |   | |  | | (___ | \\  / | |  | | (___     \n\
| |   | |  | |\\___ \\| |\\/| | |  | |\\___ \\\n\
| |___| |__| |____) | |  | | |__| |____) |    \n\
 \\_____\\____/|_____/|_|  |_|\\____/|_____/  \n\
";

REGISTER_COSMOS_DATA(
    signature_asciiart,
    &cosmos_signature_asciiart,
    sizeof(cosmos_signature_asciiart)
);