# ############################################################################ #
#                                                                              #
#                                                         :::      ::::::::    #
#    cmd.py                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: charles <charles.cabergs@gmail.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/15 15:11:46 by charles           #+#    #+#              #
#    Updated: 2021/02/27 12:07:29 by cacharle         ###   ########.fr        #
#                                                                              #
# ############################################################################ #

import distutils

from minishell_test import hooks
from minishell_test.config import Config
from minishell_test.suite.decorator import suite


@suite()
def suite_redirection(test):
    """ append/write/read redirections """
    test("echo bonjour > test", setup="", files=["test"])
    test("echo > test bonjour", setup="", files=["test"])
    test("> test echo bonjour", setup="", files=["test"])
    test("echo bonjour >> test", setup="", files=["test"])
    test("echo >> test bonjour", setup="", files=["test"])
    test(">> test echo bonjour", setup="", files=["test"])
    test("cat < test", setup="echo bonjour > test")
    test("echo bonjour > test", setup="", files=["test"])
    test("echo > test'sticked' bonjour", setup="", files=["teststicked"])
    test("> test'sticked' echo bonjour", setup="", files=["teststicked"])
    test("echo bonjour >> test'sticked'", setup="", files=["teststicked"])
    test("echo >> test'sticked' bonjour", setup="", files=["teststicked"])
    test(">> test'sticked' echo bonjour", setup="", files=["teststicked"])
    test("cat < test'sticked'", setup="echo bonjour > test'sticked'")
    test("< test'sticked' cat", setup="echo bonjour > test'sticked'")
    test("echo > test\"sticked\" bonjour", setup="", files=["teststicked"])
    test("> test\"sticked\" echo bonjour", setup="", files=["teststicked"])
    test("echo bonjour >> test\"sticked\"", setup="", files=["teststicked"])
    test("echo >> test\"sticked\" bonjour", setup="", files=["teststicked"])
    test(">> test\"sticked\" echo bonjour", setup="", files=["teststicked"])
    test("cat < test\"sticked\"", setup="echo bonjour > test\"sticked\"")
    test("< test\"sticked\" cat", setup="echo bonjour > test\"sticked\"")
    test("echo > test'yo'\"sticked\" bonjour", setup="", files=["testyosticked"])
    test("> test'yo'\"sticked\" echo bonjour", setup="", files=["testyosticked"])
    test("echo bonjour >> test'yo'\"sticked\"", setup="", files=["testyosticked"])
    test("echo >> test'yo'\"sticked\" bonjour", setup="", files=["testyosticked"])
    test(">> test'yo'\"sticked\" echo bonjour", setup="", files=["testyosticked"])
    test("cat < test'yo'\"sticked\"", setup="echo bonjour > test'yo'\"sticked\"")
    test("< test'yo'\"sticked\" cat", setup="echo bonjour > test'yo'\"sticked\"")
    test("echo bonjour > test > je > suis", setup="", files=["test", "je", "suis"])
    test("echo > test > je bonjour > suis", setup="", files=["test", "je", "suis"])
    test("> test echo bonjour > je > suis", setup="", files=["test", "je", "suis"])
    test("echo bonjour >> test > je >> suis", setup="", files=["test", "je", "suis"])
    test("echo >> test bonjour > je > suis", setup="", files=["test", "je", "suis"])
    test(">> test echo > je bonjour > suis", setup="", files=["test", "je", "suis"])
    test("cat < test < je", setup="echo bonjour > test; echo salut > je")
    test("echo bonjour>test>je>suis", setup="", files=["test", "je", "suis"])
    test(">test echo bonjour>je>suis", setup="", files=["test", "je", "suis"])
    test("echo bonjour>>test>je>>suis", setup="", files=["test", "je", "suis"])
    test("cat<test<je", setup="echo bonjour > test; echo salut > je")
    test("echo bonjour > a'b'c'd'e'f'g'h'i'j'k'l'm'n'o'p'q'r's't'u'v'w'x'y'z'",
         files=["abcdefghijklmnopqrstuvwxyz"])
    test('echo bonjour > a"b"c"d"e"f"g"h"i"j"k"l"m"n"o"p"q"r"s"t"u"v"w"x"y"z"',
         files=["abcdefghijklmnopqrstuvwxyz"])
    test('echo bonjour > a\'b\'c"d"e\'f\'g"h"i\'j\'k"l"m\'n\'o"p\'q\'r"s\'t\'u"v"w"x"y\'z\'',
         files=["abcdefghijklmnopqrstuvwxyz"])
    test("> file", files=["file"])
    test("< file", setup="echo bonjour > file")
    test(">", hook=hooks.error_line0, hook_status=hooks.platform_status(1, 2))
    test(">>", hook=hooks.error_line0, hook_status=hooks.platform_status(1, 2))
    test("<", hook=hooks.error_line0, hook_status=hooks.platform_status(1, 2))
    test("echo >", hook=hooks.error_line0, hook_status=hooks.platform_status(1, 2))
    test("echo >>", hook=hooks.error_line0, hook_status=hooks.platform_status(1, 2))
    test("echo <", hook=hooks.error_line0, hook_status=hooks.platform_status(1, 2))
    test("> test", files=["test"])
    test(">> test", files=["test"])
    test("< test", setup="touch test")
    test("echo foo >>> bar", hook=hooks.error_line0, hook_status=hooks.platform_status(1, 2))
    test("echo foo >>>> bar", hook=hooks.error_line0, hook_status=hooks.platform_status(1, 2))
    test("echo foo >>>>> bar", hook=hooks.error_line0, hook_status=hooks.platform_status(1, 2))
    test("cat << < bar", setup="echo bonjour > bar", hook=hooks.error_line0, hook_status=hooks.platform_status(1, 2))
    test("cat << << bar", setup="echo bonjour > bar", hook=hooks.error_line0, hook_status=hooks.platform_status(1, 2))
    test("cat <<<<< bar", setup="echo bonjour > bar", hook=hooks.error_line0, hook_status=hooks.platform_status(1, 2))
    test("cat < doesnotexist")
    test("echo bonjour >> a", setup="echo a > a", files=["a"])
    test("echo bonjour >> a >> a", setup="echo a > a", files=["a"])
    test("echo bonjour > a", setup="echo a > a", files=["a"])
    test("echo bonjour > a >> a", setup="echo a > a", files=["a"])


@suite()
def suite_cmd(test):
    """ long cmd, cmd not found tests """
    test("notfound")
    test("notfound a b c")
    test('echo "\\"" >>a"b""c"  ', files=["abc"])
    test("echo " + ''.join([chr(i) for i in range(1, 127) if chr(i) not in '\n`"\'()|&><']))
    test("echo foo>bar", files=["bar"])
    test("echo foo >bar", files=["bar"])
    test("echo foo> bar", files=["bar"])
    test("echo foo > bar", files=["bar"])
    test("echo a as df sad f as df qw e  qwe  as df asd f as df as d fas d f"
         "asd f asd f asdf asdf  asdf  asd f asd f asd f asd f as df as df a"
         "asd f asd f asdf asdf  asdf  asd f asd f asd f asd f as df as df a"
         "asd f asd f asdf asdf  asdf  asd f asd f asd f asd f as df as df a")
    test("echo " + Config.lorem * 10)
    test("echo " + Config.lorem * 20)


@suite()
def suite_status(test):
    """ $? tests """
    test("echo $?")
    test("echo; echo $?")
    test("notfound; echo $?")
    test("cat < doesntexist; echo $?")
    test("cat < noperm; echo $?", setup="echo bonjour > noperm; chmod 000 noperm")
    test("echo")
    test("notfound")
    test("cat < doesntexist")
    test("cat < noperm", setup="echo bonjour > noperm; chmod 000 noperm")


@suite()
def suite_cmd_path(test):
    """ cmd is a relative path, permissions on executable """
    ls_path = distutils.spawn.find_executable("ls")
    if ls_path is None:
        print("Couldn't find `ls` in your PATH: Skipping suite")
        return
    cat_path = distutils.spawn.find_executable("cat")
    if cat_path is None:
        print("Couldn't find `cat` in your PATH: Skipping suite")
        return
    test(ls_path, setup="touch a b c")
    test(ls_path + " -l", setup="touch a b c")
    test("./bonjour", setup="touch a b c; cp {} bonjour".format(ls_path))
    test("./bonjour -l", setup="touch a b c; cp {} bonjour".format(ls_path))
    test("./somedir/bonjour -l",
         setup="mkdir somedir; touch a b c; touch somedir/d somedir/e;"
               "cp {} somedir/bonjour".format(ls_path))
    test("./ls . a b c",
         setup="touch a b c; echo bonjour > a; cp {} ls".format(cat_path))
    test("ls . a b c",
         setup="touch a b c; echo bonjour > a; cp {} ls".format(cat_path))
    test("./somefile", setup="echo > somefile; chmod 000 somefile")
    test("./somefile", setup="echo > somefile; chmod 001 somefile")
    test("./somefile", setup="echo > somefile; chmod 002 somefile")
    test("./somefile", setup="echo > somefile; chmod 003 somefile")
    test("./somefile", setup="echo > somefile; chmod 004 somefile")
    test("./somefile", setup="echo > somefile; chmod 005 somefile")
    test("./somefile", setup="echo > somefile; chmod 006 somefile")
    test("./somefile", setup="echo > somefile; chmod 007 somefile")
    test("./somefile", setup="echo > somefile; chmod 010 somefile")
    test("./somefile", setup="echo > somefile; chmod 020 somefile")
    test("./somefile", setup="echo > somefile; chmod 030 somefile")
    test("./somefile", setup="echo > somefile; chmod 040 somefile")
    test("./somefile", setup="echo > somefile; chmod 050 somefile")
    test("./somefile", setup="echo > somefile; chmod 060 somefile")
    test("./somefile", setup="echo > somefile; chmod 070 somefile")
    test("./somefile", setup="echo > somefile; chmod 100 somefile")
    test("./somefile", setup="echo > somefile; chmod 200 somefile")
    test("./somefile", setup="echo > somefile; chmod 300 somefile")
    test("./somefile", setup="echo > somefile; chmod 400 somefile")
    test("./somefile", setup="echo > somefile; chmod 500 somefile")
    test("./somefile", setup="echo > somefile; chmod 600 somefile")
    test("./somefile", setup="echo > somefile; chmod 700 somefile")
    test("./somefile", setup="echo > somefile; chmod 755 somefile")
    test("./somefile", setup="echo > somefile; chmod 644 somefile")
    test("./somefile", setup="echo > somefile; chmod 311 somefile")
    test("./somefile", setup="echo > somefile; chmod 111 somefile")
    test("./somefile", setup="echo > somefile; chmod 222 somefile")
    test("./somefile", setup="echo > somefile; chmod 333 somefile")
    test("somedir/",   setup="mkdir somedir", hook=hooks.is_directory)
    test("./somedir/", setup="mkdir somedir", hook=hooks.is_directory)
    test("somedir",    setup="mkdir somedir")
    test("./somedir",  setup="mkdir somedir", hook=hooks.is_directory)
    test("somedir",    setup="mkdir somedir")
    test("somedirsoftlink/",   setup="mkdir somedir; ln -s somedir somedirsoftlink", hook=hooks.is_directory)
    test("./somedirsoftlink/", setup="mkdir somedir; ln -s somedir somedirsoftlink", hook=hooks.is_directory)
    test("somedirsoftlink",    setup="mkdir somedir; ln -s somedir somedirsoftlink")
    test("./somedirsoftlink",  setup="mkdir somedir; ln -s somedir somedirsoftlink", hook=hooks.is_directory)
    test("somedirsoftlink",    setup="mkdir somedir; ln -s somedir somedirsoftlink")
    test("./someremovedlink",  setup="touch somefile; ln -s somefile someremovedlink; rm -f somefile")
    test("./somelink2", setup="touch somefile; ln -s somefile somelink1; ln -s somelink1 somelink2")
    test("./somelink3", setup="touch somefile; ln -s somefile somelink1; ln -s somelink1 somelink2;"
                              "ln -s somelink2 somelink3")
    test("./somelink4", setup="touch somefile; ln -s somefile somelink1; ln -s somelink1 somelink2;"
                              "ln -s somelink2 somelink3; ln -s somelink3 somelink4")
    test("./somelink2ls", setup="cp " + ls_path + " somefile;"
                                "ln -s somefile somelink1; ln -s somelink1 somelink2")
    test("./somelink3ls", setup="cp " + ls_path + " somefile;"
                                "ln -s somefile somelink1; ln -s somelink1 somelink2;"
                                "ln -s somelink2 somelink3")
    test("./somelink4ls", setup="cp " + ls_path + " somefile;"
                                "ln -s somefile somelink1; ln -s somelink1 somelink2;"
                                "ln -s somelink2 somelink3; ln -s somelink3 somelink4")
    test("_", setup="touch _")
    test("'-'", setup="touch -")
    test("./_", setup="touch _")
    test("./-", setup="touch a; mv a ./-")
    test("./.", setup="touch .", hook=hooks.is_directory)
    test("./..", setup="touch ..", hook=hooks.is_directory)
    test("./somefile", setup='echo > somefile && chmod 0777 somefile')
    test("./somefile", setup='echo > somefile && chmod 1000 somefile')
    test("./somefile", setup='echo > somefile && chmod 2000 somefile')
    test("./somefile", setup='echo > somefile && chmod 3000 somefile')
    test("./somefile", setup='echo > somefile && chmod 4000 somefile')
    test("./somefile", setup='echo > somefile && chmod 5000 somefile')
    test("./somefile", setup='echo > somefile && chmod 6000 somefile')
    test("./somefile", setup='echo > somefile && chmod 7000 somefile')
    test("./somefile", setup='echo > somefile && chmod 1777 somefile')
    test("./somefile", setup='echo > somefile && chmod 2777 somefile')
    test("./somefile", setup='echo > somefile && chmod 3777 somefile')
    test("./somefile", setup='echo > somefile && chmod 4777 somefile')
    test("./somefile", setup='echo > somefile && chmod 5777 somefile')
    test("./somefile", setup='echo > somefile && chmod 6777 somefile')
    test("./somefile", setup='echo > somefile && chmod 7777 somefile')
    test("./somefile", setup='echo > somefile && chmod 0000 somefile')
    test("./somedir", setup='mkdir -m 0777 somedir', hook=hooks.is_directory)
    test("./somedir", setup='mkdir -m 1000 somedir', hook=hooks.is_directory)
    test("./somedir", setup='mkdir -m 2000 somedir', hook=hooks.is_directory)
    test("./somedir", setup='mkdir -m 3000 somedir', hook=hooks.is_directory)
    test("./somedir", setup='mkdir -m 4000 somedir', hook=hooks.is_directory)
    test("./somedir", setup='mkdir -m 5000 somedir', hook=hooks.is_directory)
    test("./somedir", setup='mkdir -m 6000 somedir', hook=hooks.is_directory)
    test("./somedir", setup='mkdir -m 7000 somedir', hook=hooks.is_directory)
    test("./somedir", setup='mkdir -m 1777 somedir', hook=hooks.is_directory)
    test("./somedir", setup='mkdir -m 2777 somedir', hook=hooks.is_directory)
    test("./somedir", setup='mkdir -m 3777 somedir', hook=hooks.is_directory)
    test("./somedir", setup='mkdir -m 4777 somedir', hook=hooks.is_directory)
    test("./somedir", setup='mkdir -m 5777 somedir', hook=hooks.is_directory)
    test("./somedir", setup='mkdir -m 6777 somedir', hook=hooks.is_directory)
    test("./somedir", setup='mkdir -m 0000 somedir', hook=hooks.is_directory)
    test("./Somefile", setup='echo > somefile && chmod 000 somefile')
    test("./someFILE", setup='echo > somefile && chmod 000 somefile')


# @suite(bonus=True)
# def suite_cmd_variable(test):
#     test("A=a sh -c 'echo $A'")
#     test("A=a B=b sh -c 'echo $A$B'")
#     test("A=a B=b C=c D=d E=e F=f G=g H=h sh -c 'echo $A$B$C$D$E$F$G$H'")
#     test("A=a A=bonjour sh -c 'echo $A'")
#     test("A=aA=bonjour sh -c 'echo $A'")
#     test("BONJOURJESUIS=a sh -c 'echo $BONJOURJESUIS'")
#     test("bonjourjesuis=a sh -c 'echo $bonjourjesuis'")
#     test("bonjour_je_suis=a sh -c 'echo $bonjour_je_suis'")
#     test("BONJOURJESUIS1=a sh -c 'echo $BONJOURJESUIS1'")
#     test("bO_nJq123o__1ju_je3234sui__a=a sh -c 'echo $bO_nJq123o__1ju_je3234sui__a'")
#     test("a0123456789=a sh -c 'echo $a0123456789'")
#     test("abcdefghijklmnopqrstuvwxyz=a sh -c 'echo $abcdefghijklmnopqrstuvwxyz'")
#     test("ABCDEFGHIJKLMNOPQRSTUVWXYZ=a sh -c 'echo $ABCDEFGHIJKLMNOPQRSTUVWXYZ'")
#     test("__________________________=a sh -c 'echo $__________________________'")
#     test("_bonjour_=a sh -c 'echo $_bonjour_'")
#     test("_=a sh -c 'echo $_a'")
#     test("1=a")
#     test("BONJOURJESUIS =a sh -c 'echo $BONJOURJESUIS '")
#     test("BONJOURJESUIS= a sh -c 'echo $BONJOURJESUIS'")
#     test(r"BONJOUR\\JESUIS=a sh -c 'echo $BONJOUR\\JESUIS'")
#     test(r'BONJOUR\'JESUIS=a sh -c "echo $BONJOUR\'JESUIS"')
#     test(r'BONJOUR\"JESUIS=a sh -c "echo $BONJOUR\"JESUIS"')
#     test(r"BONJOUR\$JESUIS=a sh -c 'echo $BONJOUR\$JESUIS'")
#     test(r"BONJOUR\&JESUIS=a sh -c 'echo $BONJOUR\&JESUIS'")
#     test(r"BONJOUR\|JESUIS=a sh -c 'echo $BONJOUR\|JESUIS'")
#     test(r"BONJOUR\;JESUIS=a sh -c 'echo $BONJOUR\;JESUIS'")
#     test(r"BONJOUR\_JESUIS=a sh -c 'echo $BONJOUR\_JESUIS'")
#     test(r"BONJOUR\0JESUIS=a sh -c 'echo $BONJOUR\0JESUIS'")
#     test(r"\B\O\N\ \ \ \ \ \ \ JOURJESUIS=a sh -c 'echo $\B\O\N\ \ \ \ \ \ \ JOURJESUIS'")
#     test(r"A=\B\O\N\ \ \ \ \ \ \ JOURJESUIS sh -c 'echo $A'")
#     test(r"A='bonjour je suis charles' sh -c 'echo $A'")
#     test(r'A="bonjour je suis charles" sh -c "echo $A"')
#     test(r"A==a sh -c 'echo $A'")
#     test(r"A===a sh -c 'echo $A'")
#     test(r"A====a sh -c 'echo $A'")
#     test(r"A=====a sh -c 'echo $A'")
#     test(r"A======a sh -c 'echo $A'")
#     test(r"A=a=a=a=a=a sh -c 'echo $A'")
#
#     test("A=a; echo $A")
#     test("A=a B=b; echo $A$B")
#     test("A=a B=b C=c D=d E=e F=f G=g H=h; echo $A$B$C$D$E$F$G$H")
#     test("A=a A=bonjour; echo $A")
#     test("A=aA=bonjour; echo $A")
#     test("BONJOURJESUIS=a; echo $BONJOURJESUIS")
#     test("bonjourjesuis=a; echo $bonjourjesuis")
#     test("bonjour_je_suis=a; echo $bonjour_je_suis")
#     test("BONJOURJESUIS1=a; echo $BONJOURJESUIS1")
#     test("bO_nJq123o__1ju_je3234sui__a=a; echo $bO_nJq123o__1ju_je3234sui__a")
#     test("a0123456789=a; echo $a0123456789")
#     test("abcdefghijklmnopqrstuvwxyz=a; echo $abcdefghijklmnopqrstuvwxyz")
#     test("ABCDEFGHIJKLMNOPQRSTUVWXYZ=a; echo $ABCDEFGHIJKLMNOPQRSTUVWXYZ")
#     test("__________________________=a; echo $__________________________")
#     test("_bonjour_=a; echo $_bonjour_")
#     test("_=a; echo $_a")
#     test("BONJOURJESUIS =a; echo $BONJOURJESUIS ")
#     test("BONJOURJESUIS= a; echo $BONJOURJESUIS")
#     test(r"BONJOUR\\JESUIS=a; echo $BONJOUR\\JESUIS")
#     test(r"BONJOUR\'JESUIS=a; echo $BONJOUR\'JESUIS")
#     test(r'BONJOUR\"JESUIS=a; echo $BONJOUR\"JESUIS')
#     test(r"BONJOUR\$JESUIS=a; echo $BONJOUR\$JESUIS")
#     test(r"BONJOUR\&JESUIS=a; echo $BONJOUR\&JESUIS")
#     test(r"BONJOUR\|JESUIS=a; echo $BONJOUR\|JESUIS")
#     test(r"BONJOUR\;JESUIS=a; echo $BONJOUR\;JESUIS")
#     test(r"BONJOUR\_JESUIS=a; echo $BONJOUR\_JESUIS")
#     test(r"BONJOUR\0JESUIS=a; echo $BONJOUR\0JESUIS")
#     test(r"\B\O\N\ \ \ \ \ \ \ JOURJESUIS=a; echo $\B\O\N\ \ \ \ \ \ \ JOURJESUIS")
#     test(r"A=\B\O\N\ \ \ \ \ \ \ JOURJESUIS; echo $A")
#     test(r"A='bonjour je suis charles'; echo $A")
#     test(r'A="bonjour je suis charles"; echo $A')
#     test(r"A==a; echo $A")
#     test(r"A===a; echo $A")
#     test(r"A====a; echo $A")
#     test(r"A=====a; echo $A")
#     test(r"A======a; echo $A")
#     test(r"A=a=a=a=a=a; echo $A")
#
#     test("PATH=a ls")
#     test("PATH=a echo aa")
#     test("A=a echo $A")
#     test("A=a B=b echo $A$B")
#     test("A=a B=b C=c D=d E=e F=f G=g H=h echo $A$B$C$D$E$F$G$H")
#     test("A=$PATH sh -c 'echo $A'")
#     test("A=\"$PATH je  suis\" sh -c 'echo $A'")
#     test("A='$PATH je  suis' sh -c 'echo $A'")
#     test("$TEST sh -c 'echo $A'", setup="export TEST='A=a'")
#     test("'BONJOURJESUIS''=''a' sh -c 'echo $BONJOURJESUIS'")
#     test('"BONJOURJESUIS""=""a" sh -c "echo $BONJOURJESUIS"')
#     test("./somedir", setup='mkdir somedir && chmod 0000 somedir')
