 inherit ROOM;
#include <ansi.h> 
void create() 
{
        set("short", "����̨");
        set("long", @LONG
�ݳ�����һ��С����С���ϻ���һ�����ڣ���������һ��ľ��é��������̨��
�ǹ�ʱ�������϶��ң�ʿ����ȼ���ĵط����Ǹ�һ����Զ��һ���ɫ�Ĵ�������
��ɳ�зɾ�������һ�������������������˿�����������ʺ���֣�ȴ�����˵�
Ѫ���ᡣ���¾��������õ�ӭ������
LONG
        );
        set("exits", ([ 
                "north":        __DIR__"grassland4",
        ]));
        set("objects", ([
        ]) );
        set("outdoors", "biancheng");
        set("coor/x",0);
        set("coor/y",0);
        set("coor/z",0);
        setup();
        replace_program(ROOM);
}    