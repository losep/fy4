 // Copyright (c) apstone, inc.
inherit ITEM;
inherit F_LIQUID;
void create()
{
    set_name("ţƤ��", ({ "cow skin", "skin" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "һ��ţƤ��Ĵ������װ�ðˡ�������Һ�塣\n");
                set("unit", "��");
                set("value", 20);
                set("max_liquid", 15);
        } 
        set("liquid", ([
                "type": "water",
                "name": "ɳ��֭",
                "remaining": 15,
                "drunk_apply": 0,
        ]) );
        ::init_item();
}       
