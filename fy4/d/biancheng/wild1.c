 inherit ROOM;
#include <ansi.h> 
void create() 
{
        set("short", "��ԭ");
        set("long", @LONG
����������������ƽ̹����������أ������������ɳ�����ޱ��޼ʵĻ�ԭ
��������������û��·�����������˳������ˣ�̤��һ�����߿��ĳ��������ĵ�
�������ǳ��޻����ĺۼ���ż����������۹�������ǰ����С��
LONG
        );
        set("exits", ([ 
        "east" : AREA_EREN"yuzhu",
        "west" : __DIR__"wild2",
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