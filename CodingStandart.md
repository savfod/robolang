# Правила #

За основу правил использования имен принято: "Соглашение по оформлению кода команы RSDN"

http://www.rsdn.ru/article/mag/200401/codestyle.XML
## А именно: ##
  * Имена локальных переменных - Кэмел (`xxxYyyyZzz`)
  * Параметры в функциях, методах - Кэмел
  * Непубличные поля - Кэмел
  * Классы, структуры - Паскаль (`XxxYyyyZzz`)
  * стиль оформления блоков:
```
if( a == 2009 )
{
    b = a;
}
```
  * Использование пробелов:
```
for( int k = hc -> GetItemCount() - 2; k >= 0; k-- )
```
## Исключения ##
  * Названия классов пишутся с префиксом C (Например, CString, CRobot, CColor)
  * Публичные поля - Кэмел
  * Методы - Кэмел, кроме сгенерированых средой. (class wizard)
## Кроме того ##
  * При использовании указателей, предпочтительнее запись (в смысле положения звёздочки):
```
Aaaa *bbbb
```
  * Функции компонента ProgramUI вызываются как из компонента Programm, так и из компонента VC60, окна CRobotEditWindow, вследствие чего функции ProgramUI называются с префиксами onEdit и onProgram, в зависимости от того, кто их вызывает.
  * Функции реагирующие на события именуются по названию события, а не по тому, что они должны делать.
  * Daily commits to have fresh code. It means:
- at the end of the day you make commits (if you have some coding this day)
- commit should not break anything that was working before (and, of course, does not lead to broken build)