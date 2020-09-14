/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Unikraft Monkey Animation
 *
 * Authors: Simon Kuenzer <simon.kuenzer@neclab.eu>
 *
 *
 * Copyright (c) 2020, NEC Laboratories Europe GmbH, NEC Corporation.
 *                     All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef MONKEY_H
#define MONKEY_H

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#endif /* ARRAY_SIZE */

static const char *monkey3[] = {
	"     _               ",
	"   c'_'o  .--'       ",
	"   (| |)_/           ",

	"     _               ",
	"   c'o'o  .--.       ",
	"   (| |)_/           ",

	"     _               ",
	"   c'_'o  .-.        ",
	"   (| |)_/   `       ",

	"     _               ",
	"   c'o'o  .--.       ",
	"   (| |)_/           ",

	"     _               ",
	"   c'_'o  .--'       ",
	"   (| |)_/           ",

	"     _               ",
	"   c'_'o  .--.       ",
	"   (| |)_/           ",

	"     _               ",
	"   c'_'o  .-.        ",
	"   (| |)_/   `       ",

	"     _               ",
	"   c'_'o  .--.       ",
	"   (| |)_/           ",

	"     _               ",
	"   c-_-o  .--'       ",
	"   (| |)_/           ",

	"     _               ",
	"   c'_'o  .--.       ",
	"   (| |)_/           ",

	"     _               ",
	"   c'_'o  .-.        ",
	"   (| |)_/   `       ",

	"     _               ",
	"   c'_'o  .--.       ",
	"   (| |)_/           ",

	".---    _            ",
	"`--,___c \".          ",
	"   (,--( \\           ",

	".--      _           ",
	"`---,___c \".         ",
	"    ( \\-(,           ",

	".-        _          ",
	"`---'\\___c \".        ",
	"     (,--( \\         ",

	".    _     _         ",
	"`---' \\___c \".       ",
	"      ( \\-(,         ",

	"     _      _        ",
	"`---' `,___c \".      ",
	"       (,--( \\       ",

	"     _       _       ",
	" ---' `-,___c \".     ",
	"        ( \\-(,       ",

	"     _        _      ",
	"  --' `--,___c \".    ",
	"         (,--( \\     ",

	"     _         _     ",
	"   -' `---,___c \".   ",
	"          ( \\-(,     ",

	"     _          _    ",
	"    ' `---'\\___c \".  ",
	"           (,--( \\   ",

	"     _     _     _   ",
	"      `---' \\___c \". ",
	"            ( \\-(,   ",

	"           _    _    ",
	"      `---' | c   o  ",
	"            \\_(|,|)  ",

	"             _  .---.",
	"           .\" o___,-'",
	"            / )--,)  ",

	"            _    ---.",
	"          .\" o___,--'",
	"            ,)-/ )   ",

	"           _      --.",
	"         .\" o___,---'",
	"          / )--,)    ",

	"          _        -.",
	"        .\" o___/`---'",
	"          ,)-/ )     ",

	"         _     _    .",
	"       .\" o___/ `---'",
	"        / )--,)      ",

	"        _      _     ",
	"      .\" o___,' `---'",
	"        ,)-/ )       ",

	"       _       _     ",
	"     .\" o___,-' `--- ",
	"      / )--,)        ",

	"      _        _     ",
	"    .\" o___,--' `--  ",
	"      ,)-/ )         ",

	"     _         _     ",
	"   .\" o___,---' `-   ",
	"     / )-,)          ",

	"    _          _     ",
	"  .\" o___,----' `    ",
	"    ,)-/ )           ",
};

#define monkey3_frame_count (ARRAY_SIZE(monkey3) / 3)

#endif /* MONKEY_H */
