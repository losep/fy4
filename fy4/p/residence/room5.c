 inherit ROOM;
void create ()
{
  set ("short", "̩���㳡");
  set ("long", @LONG
�������������ܵ��������е��徻����ɫʯ���̳ɵĴ�����ķ����ӡ��㳡
�����Σ�����������ڴ�Ĳ�ɫʯ���̳ɣ��������̣�ɷ�Ǻÿ����㳡���и���
ˮ�أ�������Ϻ��浹Ҳ���˲��٣������ļ��紺�������£��ɻ�˯���ޱ���次�
LONG);
        set("exits", ([
  "northeast" : __DIR__"room7",
  "southeast" : __DIR__"room4",
]));
        set("coor/x",5);
        set("coor/y",2035);
        set("coor/z",40);
        set("owner","public");
        setup();
  replace_program(ROOM); 
}      