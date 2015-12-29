#include <ansi.h>
inherit ROOM;
string *names=({
        __DIR__"cemetery10",
        __DIR__"cemetery8",
        __DIR__"cemetery4",
        
} );  
void create()
{
        set("short", "�س�");
        set("long", @LONG
��ɫ��ɭ����Ҳ���䣬Զ���ߵ�������ص����ĺ��澹��һƬ�ޱ��޼ʵĻķء�
��Ȼ�ǰ��죬�ķؼ���Ȼ����������Ҳ��Ȼ���Թ����ˡ����������������Ե�������
�谵������У�һֻ��Ӱ�����������������������������������м������硣����
Ҳ����ɽ����ˮ����Ұ���ķء�
LONG
        );
        set("outdoors", "biancheng");
        set("coor/x",0);
        set("coor/y",0);
        set("coor/z",0);
        setup();
} 
void reset()
{
        int i,j;
        string temp;
        ::reset();
        for (i=0;i<=2;i++)
        {
                j=random(3);
                temp=names[j];
                names[j]=names[i];
                names[i]=names[j];
                names[i]=temp;
        }
        set("exits", ([
                "north" : __DIR__"cemetery_a",
                "south" : names[0],
           "east" : names[1],
                "west" : names[2],
        ]));
}  
int valid_leave(object obj, string dir){
        object another;
        seteuid(getuid());
        
        if (!present("zombie", this_object()) && random(10)>7) {
                another = new(__DIR__"npc/zombie3");
                another->move(environment(obj));
                message_vision(YEL"�ض�������վ��һ��������������!\n"NOR, obj); 
                return notify_fail(another->name()+"������צ�ص����������ǰ��\n");
        }       
        return 1;
}    