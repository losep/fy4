 inherit ROOM;
// Copyright (C) 1995, by Tie Yu and Daniel Yu. All rights reserved.
// This software can not be used, copied, or modified in any form without
// the written permission from authors. 
void create()
{
        set("short", "ç��֮��");
        set("long", @LONG
���ܹ������죬�����ܲ���Ũ�ܿ������Ҷ�ڱ��������ǳ���ʹ�˷ֲ���
��ҹ����������һ��ļž���ֻ�з紵�����ҵ�ɳɳ֮����ż��һ������Х��
�������ȷ�Ʈ�����ʡ�
LONG
        );
        set("exits", ([ /* sizeof() == 4 */
  "east" : __DIR__"dummy4",
  "west" : __DIR__"dummy4",
  "south" : __DIR__"center4", 
]));
        set("objects", ([
                __DIR__"npc/tiger" : 1,
                __DIR__"npc/wolf" : 1,
                __DIR__"npc/snake" : 1,
                __DIR__"npc/bear" : 2,
       ]) );
        set("outdoors", "manglin");
        set("coor/x",10);
        set("coor/y",-550);
        set("coor/z",10);
        setup();
replace_program(ROOM); 
}    