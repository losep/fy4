 // TIE@FY3
#include <weapon.h>
#include <ansi.h>
inherit SWORD;
void create()
{
        set_name(HIW "�����"NOR, ({ "cang qiong" }) );
        set_weight(10000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "һ��û�н�ͷ�ĳ���\n");
                set("value", 50000);
                set("material", "steel");
        }
        ::init_sword(50);
}  