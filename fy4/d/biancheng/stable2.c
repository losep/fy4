 inherit ROOM;
#include <ansi.h> 
void create() 
{
        set("short", "����");
        set("long", @LONG
�����õ����Ǿ�Ȼ��һ����ס�����ӻ�Ҫ���������������˸ߣ�������һ����
�ź��̺���ߵ������Ը���һ����С�䣬���ŵ���ǧ��ѡһ������������������
�������׳���е��ںڵ�Ƥë��˿��һ�����⣬�еĻ������£���̿��࣬�ް��
��ë��ż��������ǣ����һƥ�����ߺ����ܵģ���ˮϴ��һ����
LONG
        );
        set("exits", ([ 
                "south": __DIR__"stable1",
        ]));
        set("objects", ([
        ]) );
        set("coor/x",0);
        set("coor/y",0);
        set("coor/z",0);
        setup();
        replace_program(ROOM);
} 