/*
Exercise 1-2. Experiment to find out what happens when prints's argument string
contains \c, where c is some character not listed above.

matxo
*/

#include <stdio.h>

int main(void)
{
//  printf ("32. c Hello\cWorld!\n");       // replace c with random character
    printf ("32.   Hello\ World!\n");       // unknown escape sequence
    printf ("33. ! Hello\!World!\n");       // unknown escape sequence
    printf ("34. \" Hello\"World!\n");      // double quote
    printf ("35. # Hello\#World!\n");       // unknown escape sequence
    printf ("36. $ Hello\$World!\n");       // unknown escape sequence
    printf ("37. % Hello\%World!\n");       // unknown escape sequence
    printf ("38. & Hello\&World!\n");       // unknown escape sequence
    printf ("39. ' Hello\'World!\n");       // single quote
    printf ("40. ( Hello\(World!\n");       // unknown escape sequence
    printf ("41. ) Hello\)World!\n");       // unknown escape sequence
    printf ("42. * Hello\*World!\n");       // unknown escape sequence
    printf ("43. + Hello\+World!\n");       // unknown escape sequence
    printf ("44. , Hello\,World!\n");       // unknown escape sequence
    printf ("45. - Hello\-World!\n");       // unknown escape sequence
    printf ("46. . Hello\.World!\n");       // unknown escape sequence
    printf ("47. / Hello\/World!\n");       // unknown escape sequence
    printf ("48. 0 Hello\0World!\n");       // octal value
    printf ("49. 1 Hello\1World!\n");       // octal value
    printf ("50. 2 Hello\2World!\n");       // octal value
    printf ("51. 3 Hello\3World!\n");       // octal value
    printf ("52. 4 Hello\4World!\n");       // octal value
    printf ("53. 5 Hello\5World!\n");       // octal value
    printf ("54. 6 Hello\6World!\n");       // octal value
    printf ("55. 7 Hello\7World!\n");       // octal value
    printf ("56. 8 Hello\8World!\n");       // unknown escape sequence
    printf ("57. 9 Hello\9World!\n");       // unknown escape sequence
    printf ("58. : Hello\:World!\n");       // unknown escape sequence
    printf ("59. ; Hello\;World!\n");       // unknown escape sequence
    printf ("60. < Hello\<World!\n");       // unknown escape sequence
    printf ("61. = Hello\=World!\n");       // unknown escape sequence
    printf ("62. > Hello\>World!\n");       // unknown escape sequence
    printf ("63. ? Hello\?World!\n");       // question mark
    printf ("64. @ Hello\@World!\n");       // at sign
    printf ("65. A Hello\AWorld!\n");       // unknown escape sequence
    printf ("66. B Hello\BWorld!\n");       // unknown escape sequence
    printf ("67. C Hello\CWorld!\n");       // unknown escape sequence
    printf ("68. D Hello\DWorld!\n");       // unknown escape sequence
    printf ("69. E Hello\EWorld!\n");       // escape character
    printf ("70. F Hello\FWorld!\n");       // unknown escape sequence
    printf ("71. G Hello\GWorld!\n");       // unknown escape sequence
    printf ("72. H Hello\HWorld!\n");       // unknown escape sequence
    printf ("73. I Hello\IWorld!\n");       // unknown escape sequence
    printf ("74. J Hello\JWorld!\n");       // unknown escape sequence
    printf ("75. K Hello\KWorld!\n");       // unknown escape sequence
    printf ("76. L Hello\LWorld!\n");       // unknown escape sequence
    printf ("77. M Hello\MWorld!\n");       // unknown escape sequence
    printf ("78. N Hello\NWorld!\n");       // unknown escape sequence
    printf ("79. O Hello\OWorld!\n");       // unknown escape sequence
    printf ("80. P Hello\PWorld!\n");       // unknown escape sequence
    printf ("81. Q Hello\QWorld!\n");       // unknown escape sequence
    printf ("82. R Hello\RWorld!\n");       // unknown escape sequence
    printf ("83. S Hello\SWorld!\n");       // unknown escape sequence
    printf ("84. T Hello\TWorld!\n");       // unknown escape sequence
    printf ("85. U Hello\U0001F30D!\n");    // universal character
    printf ("86. V Hello\VWorld!\n");       // warning: unknown escape sequence
    printf ("87. W Hello\WWorld!\n");       // warning: unknown escape sequence
    printf ("88. X Hello\XWorld!\n");       // warning: unknown escape sequence
    printf ("89. Y Hello\YWorld!\n");       // warning: unknown escape sequence
    printf ("90. Z Hello\ZWorld!\n");       // warning: unknown escape sequence
    printf ("91. [ Hello\[World!\n");       // warning: unknown escape sequence
    printf ("92. \\ Hello\\World!\n");      // backslash
    printf ("93. ] Hello\]World!\n");       // unknown escape sequence
    printf ("94. ^ Hello\^World!\n");       // unknown escape sequence
    printf ("95. _ Hello\_World!\n");       // unknown escape sequence
    printf ("96. ` Hello\`World!\n");       // unknown escape sequence
    printf ("97. a Hello\aWorld!\n");       // alert (bell)
    printf ("98. b Hello\bWorld!\n");       // backspace
    printf ("99. c Hello\cWorld!\n");       // unknown escape sequence
    printf ("100. d Hello\dWorld!\n");      // unknown escape sequence
    printf ("101. e Hello\eWorld!\n");      // escape character
    printf ("102. f Hello\fWorld!\n");      // formfeed
    printf ("103. g Hello\gWorld!\n");      // unknown escape sequence
    printf ("104. h Hello\hWorld!\n");      // unknown escape sequence
    printf ("105. i Hello\iWorld!\n");      // unknown escape sequence
    printf ("106. j Hello\jWorld!\n");      // unknown escape sequence
    printf ("107. k Hello\kWorld!\n");      // unknown escape sequence
    printf ("108. l Hello\lWorld!\n");      // unknown escape sequence
    printf ("109. m Hello\mWorld!\n");      // unknown escape sequence
    printf ("110. n Hello\nWorld!\n");      // newline
    printf ("111. o Hello\oWorld!\n");      // unknown escape sequence
    printf ("112. p Hello\pWorld!\n");      // unknown escape sequence
    printf ("113. q Hello\qWorld!\n");      // unknown escape sequence
    printf ("114. r Hello\rWorld!\n");      // carriage return
    printf ("115. s Hello\sWorld!\n");      // unknown escape sequence
    printf ("116. t Hello\tWorld!\n");      // horizontal tab
    printf ("117. u Hello\u2641!\n");       // universal character
    printf ("118. v Hello\vWorld!\n");      // vertical tab
    printf ("119. w Hello\wWorld!\n");      // unknown escape sequence
    printf ("120. x Hello\xFWorld!\n");     // hexadecimal number
    printf ("121. y Hello\yWorld!\n");      // unknown escape sequence
    printf ("122. z Hello\zWorld!\n");      // unknown escape sequence
    printf ("123. { Hello\{World!\n");      // left curly bracket
    printf ("124. | Hello\|World!\n");      // unknown escape sequence
    printf ("125. } Hello\}World!\n");      // unknown escape sequence
    printf ("126. ~ Hello\~World!\n");      // unknown escape sequence
    return 0;
}
