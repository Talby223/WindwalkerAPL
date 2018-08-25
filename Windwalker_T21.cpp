// Windwalker Pre-Combat Action Priority List ==========================

void monk_t::apl_pre_windwalker()
{
  action_priority_list_t* pre = get_action_priority_list( "precombat" );

  // Flask
  pre->add_action( "flask" );
  // Food
  pre->add_action( "food" );
  // Rune
  pre->add_action( "augmentation" );

  // Snapshot stats
  pre->add_action( "snapshot_stats", "Snapshot raid buffed stats before combat begins and pre-potting is done." );

  pre->add_action( "potion" );
  pre->add_talent( this, "Chi Burst" );
  pre->add_talent( this, "Chi Wave" );
}

// Mistweaver Pre-Combat Action Priority List ==========================

void monk_t::apl_pre_mistweaver()
{
  action_priority_list_t* pre = get_action_priority_list( "precombat" );

  // Flask
  pre->add_action( "flask" );

  // Food
  pre->add_action( "food" );

  // Rune
  pre->add_action( "augmentation" );

  // Snapshot stats
  pre->add_action( "snapshot_stats", "Snapshot raid buffed stats before combat begins and pre-potting is done." );

  pre->add_action( "potion" );

  pre->add_talent( this, "Chi Burst" );
  pre->add_talent( this, "Chi Wave" );
}

// Brewmaster Combat Action Priority List =========================

void monk_t::apl_combat_brewmaster()

{
  std::vector<std::string> racial_actions = get_racial_actions();
  action_priority_list_t* def             = get_action_priority_list( "default" );
  def->add_action( "auto_attack" );
  def->add_action( this, "Gift of the Ox", "if=health<health.max*0.65" );
  def->add_talent( this, "Dampen Harm", "if=incoming_damage_1500ms&buff.fortifying_brew.down" );
  def->add_action( this, "Fortifying Brew", "if=incoming_damage_1500ms&(buff.dampen_harm.down|buff.diffuse_magic.down)" );

  int num_items = (int)items.size();

  for ( int i = 0; i < num_items; i++ )
  {
    if ( items[ i ].has_special_effect( SPECIAL_EFFECT_SOURCE_NONE, SPECIAL_EFFECT_USE ) )
    {
      def->add_action( "use_item,name=" + items[ i ].name_str );
    }
  }
  def->add_action( "potion" );
  for ( size_t i = 0; i < racial_actions.size(); i++ )
  {
    if ( racial_actions[ i ] != "arcane_torrent" )
      def->add_action( racial_actions[ i ] );
  }
  // Ironskin Brew
  def->add_talent( this, "Invoke Niuzao, the Black Ox", "if=target.time_to_die>25" );
  def->add_action( this, "Ironskin Brew", "if=buff.blackout_combo.down&incoming_damage_1999ms>(health.max*0.1+stagger.last_tick_damage_4)&buff.elusive_brawler.stack<2&!buff.ironskin_brew.up",
                  "Ironskin Brew priority whenever it took significant damage and ironskin brew buff is missing (adjust the health.max coefficient according to intensity of damage taken), and to dump excess charges before BoB." );
  def->add_action( this, "Ironskin Brew", "if=cooldown.brews.charges_fractional>1&cooldown.black_ox_brew.remains<3" );

  // Purifying Brew
  def->add_action( this, "Purifying Brew", "if=stagger.pct>(6*(3-(cooldown.brews.charges_fractional)))&(stagger.last_tick_damage_1>((0.02+0.001*(3-cooldown.brews.charges_fractional))*stagger.last_tick_damage_30))",
                  "Purifying behaviour is based on normalization (iE the late expression triggers if stagger size increased over the last 30 ticks or 15 seconds)." );

  // Black Ox Brew
  def->add_talent( this, "Black Ox Brew","if=cooldown.brews.charges_fractional<0.5",
                  "Black Ox Brew is currently used to either replenish brews based on less than half a brew charge available, or low energy to enable Keg Smash" );
  def->add_talent( this, "Black Ox Brew", "if=(energy+(energy.regen*cooldown.keg_smash.remains))<40&buff.blackout_combo.down&cooldown.keg_smash.up" );


  def->add_action( this, "Keg Smash", "if=spell_targets>=2",
                  "Offensively, the APL prioritizes KS on cleave, BoS else, with energy spenders and cds sorted below" );
  def->add_action( this, "Tiger Palm", "if=talent.rushing_jade_wind.enabled&buff.blackout_combo.up&buff.rushing_jade_wind.up" );
  def->add_action( this, "Tiger Palm", "if=(talent.invoke_niuzao_the_black_ox.enabled|talent.special_delivery.enabled)&buff.blackout_combo.up" );
  def->add_action( this, "Blackout Strike" );
  def->add_action( this, "Keg Smash" );
  def->add_talent( this, "Rushing Jade Wind", "if=buff.rushing_jade_wind.down" );
  def->add_action( this, "Breath of Fire", "if=buff.blackout_combo.down&(buff.bloodlust.down|(buff.bloodlust.up&&dot.breath_of_fire_dot.refreshable))" );
  def->add_talent( this, "Chi Burst" );
  def->add_talent( this, "Chi Wave" );
  def->add_action( this, "Tiger Palm", "if=!talent.blackout_combo.enabled&cooldown.keg_smash.remains>gcd&(energy+(energy.regen*(cooldown.keg_smash.remains+gcd)))>=65" );
  for ( size_t i = 0; i < racial_actions.size(); i++ )
  {
    if ( racial_actions[ i ] == "arcane_torrent" )
      def->add_action( racial_actions[ i ] + ",if=energy<31" );
  }
  def->add_talent( this, "Rushing Jade Wind" );
}

// Windwalker Combat Action Priority List ===============================

void monk_t::apl_combat_windwalker()
{
  std::vector<std::string> racial_actions   = get_racial_actions();
  action_priority_list_t* def               = get_action_priority_list( "default" );
  action_priority_list_t* cd                = get_action_priority_list( "cd" );
  action_priority_list_t* sef               = get_action_priority_list( "sef" );
  action_priority_list_t* serenity          = get_action_priority_list( "serenity" );
  action_priority_list_t* serenity_opener   = get_action_priority_list( "serenity_opener" );
  action_priority_list_t* serenitySR        = get_action_priority_list( "serenitySR" );
  action_priority_list_t* serenity_openerSR = get_action_priority_list( "serenity_openerSR" );
  action_priority_list_t* aoe               = get_action_priority_list( "aoe" );
  action_priority_list_t* st                = get_action_priority_list( "st" );

  def->add_action( "auto_attack" );
  def->add_action( this, "Spear Hand Strike", "if=target.debuff.casting.react" );
  def->add_action( this, "Touch of Karma",
                   "interval=90,pct_health=0.5,if=!talent.Good_Karma.enabled,interval=90,pct_health=0.5",
                   "Touch of Karma on cooldown, if Good Karma is enabled equal to 100% of maximum health" );
  def->add_action( this, "Touch of Karma", "interval=90,pct_health=1.0,if=talent.good_karma.enabled&buff.bloodlust.down&time>1" );
  def->add_action( this, "Touch of Karma", "interval=90,pct_health=1.0,if=talent.good_karma.enabled&prev_gcd.1.touch_of_death&buff.bloodlust.up" );

  if ( sim->allow_potions )
  {
    if ( true_level >= 100 )
      def->add_action(
          "potion,if=buff.serenity.up|buff.storm_earth_and_fire.up|(!talent.serenity.enabled&trinket.proc.agility.react)|buff.bloodlust.react|target.time_to_die<=60",
          "Potion if Serenity or Storm, Earth, and Fire are up or you are running serenity and a main stat trinket "
          "procs, or you are under the effect of bloodlust, or target time to die is greater or equal to 60" );
    else
      def->add_action(
          "potion,if=buff.serenity.up|buff.storm_earth_and_fire.up|(!talent.serenity.enabled&trinket.proc.agility.react)"
          "|buff.bloodlust.react|target.time_to_die<=60" );
  }

  def->add_action( this, "Touch of Death", "if=target.time_to_die<=9" );
  def->add_action(
      "call_action_list,name=serenitySR,if=((talent.serenity.enabled&cooldown.serenity.remains<=0)|buff.serenity.up)&azerite.swift_roundhouse.enabled&time>30",
      "Call the Serenity action list if you're using Serenity and have more than two ranks of Swift Roundhouse Trait" );
  def->add_action(
      "call_action_list,name=serenity,if=((!azerite.swift_roundhouse.enabled&talent.serenity.enabled&cooldown.serenity.remains<=0)|buff.serenity.up)&time>30",
      "Call the Serenity action list if you're using Serenity and Serenity is available (or you're currently in "
      "Serenity)" );
  def->add_action(
      "call_action_list,name=serenity_openerSR,if=(talent.serenity.enabled&cooldown.serenity.remains<=0|buff.serenity.up)&time<30&azerite.swift_roundhouse.enabled",
      "Call the Serenity Opener action list if you're using Serenity and have more than two ranks of Swift Roundhouse Trait" );
  def->add_action(
      "call_action_list,name=serenity_opener,if=(!azerite.swift_roundhouse.enabled&talent.serenity.enabled&cooldown.serenity.remains<=0|buff.serenity.up)&time<30",
      "Call the Serenity Opener action list if you're using Serenity and Serenity is available (or you're currently in "
      "Serenity)" );
  def->add_action(
      "call_action_list,name=sef,if=!talent.serenity.enabled&(buff.storm_earth_and_fire.up|cooldown.storm_earth_and_fire.charges=2)",
      "Call the SEF action list if you're using SEF and are currently in SEF or have 2 SEF stacks" );
  def->add_action(
      "call_action_list,name=sef,if=(!talent.serenity.enabled&cooldown.fists_of_fury.remains<=12&chi>=3&cooldown.rising_sun_kick.remains<=1)|target.time_to_die<=25|cooldown.touch_of_death.remains>112",
      "Call the SEF action list if you're not using Serenity and:\n# - FoF cd <= 12\n# - Chi >= 3\n# - RSK cd >= 1\n# "
      "OR the target will die within 25 seconds OR ToD is on the target" );
  def->add_action(
      "call_action_list,name=sef,if=(!talent.serenity.enabled&!equipped.drinking_horn_cover&cooldown.fists_of_fury.remains<=6&chi>=3&cooldown.rising_sun_kick.remains<=1)|target.time_to_die<=15|cooldown.touch_of_death.remains>112&cooldown.storm_earth_and_fire.charges=1",
      "Call the SEF action list if you're using Serenity and:\n# - Using DHC\n# - FoF cd <= 6\n# - Chi >= 3\n# - RSK "
      "cd <= 1\n# OR the target will die within 15 seconds OR ToD is on the target and you have 1 stack of SEF" );
  def->add_action(
      "call_action_list,name=sef,if=(!talent.serenity.enabled&cooldown.fists_of_fury.remains<=12&chi>=3&cooldown.rising_sun_kick.remains<=1)|target.time_to_die<=25|cooldown.touch_of_death.remains>112&cooldown.storm_earth_and_fire.charges=1",
      "Exactly the same as previous line, but with an added check whether you have 1 stack of SEF" );
  def->add_action( "call_action_list,name=aoe,if=active_enemies>3",
                   "Call the AoE action list if there are more than 3 enemies" );
  def->add_action( "call_action_list,name=st,if=active_enemies<=3",
                   "Call the ST action list if there are 3 or less enemies" );

  // Cooldowns
  cd->add_talent( this, "Invoke Xuen, the White Tiger" );

  // On-use items
  for ( size_t i = 0; i < items.size(); i++ )
  {
    if ( items[ i ].has_special_effect( SPECIAL_EFFECT_SOURCE_ITEM, SPECIAL_EFFECT_USE ) )
    {
      if ( items[ i ].name_str == "unbridled_fury" )
        cd->add_action( "use_item,name=" + items[ i ].name_str +
                        ",if=(!talent.fist_of_the_white_tiger.enabled&cooldown.fist_of_the_white_tiger.remains<14&"
                        "cooldown.fists_of_fury.remains<=15&cooldown.rising_sun_kick.remains<7)|buff.serenity.up" );
      else if ( items[ i ].name_str == "tiny_oozeling_in_a_jar" )
        cd->add_action( "use_item,name=" + items[ i ].name_str + ",if=buff.congealing_goo.stack>=6" );
      else if ( items[ i ].name_str == "horn_of_valor" )
        cd->add_action( "use_item,name=" + items[ i ].name_str +
                        ",if=!talent.serenity.enabled|cooldown.serenity.remains<18|cooldown.serenity.remains>50|target."
                        "time_to_die<=30" );
      else if ( items[ i ].name_str == "vial_of_ceaseless_toxins" )
        cd->add_action(
            "use_item,name=" + items[ i ].name_str +
            ",if=(buff.serenity.up&!equipped.specter_of_betrayal)|(equipped.specter_of_betrayal&(time<5|cooldown."
            "serenity.remains<=8))|!talent.serenity.enabled|target.time_to_die<=cooldown.serenity.remains" );
      else if ( items[ i ].name_str == "specter_of_betrayal" )
        cd->add_action( "use_item,name=" + items[ i ].name_str +
                        ",if=(cooldown.serenity.remains>10|buff.serenity.up)|!talent.serenity.enabled" );
      else if ( ( items[ i ].name_str != "draught_of_souls" ) || ( items[ i ].name_str != "forgefiends_fabricator" ) ||
                ( items[ i ].name_str != "archimondes_hatred_reborn" ) )
        cd->add_action( "use_item,name=" + items[ i ].name_str );
    }
  }

  // Racials
  for ( size_t i = 0; i < racial_actions.size(); i++ )
  {
    if ( racial_actions[ i ] == "arcane_torrent" )
      cd->add_action( racial_actions[ i ] + ",if=chi.max-chi>=1&energy.time_to_max>=0.5",
                      "Use Arcane Torrent if you are missing at least 1 Chi and won't cap energy within 0.5 seconds" );
    else
      cd->add_action( racial_actions[ i ] );
  }

  cd->add_action( this, "Touch of Death" );

  // Storm, Earth, and Fire
  sef->add_action( this, "Tiger Palm", "target_if=min:debuff.mark_of_the_crane.remains,if=!prev_gcd.1.tiger_palm&!prev_gcd.1.energizing_elixir&energy=energy.max&chi<1" );
  sef->add_action( "call_action_list,name=cd" );
  sef->add_action( this, "Storm, Earth, and Fire", "if=!buff.storm_earth_and_fire.up" );
  sef->add_action( "call_action_list,name=aoe,if=active_enemies>3" );
  sef->add_action( "call_action_list,name=st,if=active_enemies<=3" );

  // Serenity with at least 2 ranks of Swift Roundhouse trait
  serenitySR->add_action( this, "Tiger Palm", "target_if=min:debuff.mark_of_the_crane.remains,if=!prev_gcd.1.tiger_palm&!prev_gcd.1.energizing_elixir&energy=energy.max&chi<1&!buff.serenity.up");
  serenitySR->add_action( "call_action_list,name=cd" );
  serenitySR->add_talent( this, "Serenity", "if=cooldown.rising_sun_kick.remains<=2" );
  serenitySR->add_action( this, "Fists of Fury", "if=buff.serenity.remains<=1.05" );
  serenitySR->add_action( this, "Rising Sun Kick", "target_if=min:debuff.mark_of_the_crane.remains" );
  serenitySR->add_action( this, "Blackout Kick", "target_if=min:debuff.mark_of_the_crane.remains,if=!prev_gcd.1.blackout_kick&cooldown.rising_sun_kick.remains>=2&cooldown.fists_of_fury.remains>=2" );
  serenitySR->add_action( this, "Blackout Kick", "target_if=min:debuff.mark_of_the_crane.remains" );

  // Serenity Opener
  serenity_opener -> add_talent( this, "Fist of the White Tiger", "if=buff.serenity.down" );
  serenity_opener -> add_action( this, "Tiger Palm", "target_if=min:debuff.mark_of_the_crane.remains,if=!prev_gcd.1.tiger_palm&buff.serenity.down&chi<4" );
  serenity_opener -> add_action( "call_action_list,name=cd,if=buff.serenity.down" );
  serenity_opener -> add_action( "call_action_list,name=serenity,if=buff.bloodlust.down" );
  serenity_opener -> add_talent( this, "Serenity" );
  serenity_opener -> add_action( this, "Rising Sun Kick", "target_if=min:debuff.mark_of_the_crane.remains" );
  serenity_opener -> add_action( this, "Fists of Fury", "if=prev_gcd.1.rising_sun_kick&prev_gcd.2.serenity" );
  serenity_opener -> add_action( this, "Fists of Fury", "if=prev_gcd.1.rising_sun_kick&prev_gcd.2.blackout_kick" );
  serenity_opener -> add_action( this, "Blackout Kick", "target_if=min:debuff.mark_of_the_crane.remains,if=!prev_gcd.1.blackout_kick&cooldown.rising_sun_kick.remains>=2&cooldown.fists_of_fury.remains>=2" );
  serenity_opener -> add_action( this, "Blackout Kick", "target_if=min:debuff.mark_of_the_crane.remains,if=!prev_gcd.1.blackout_kick" );

  // Serenity
  serenity->add_action( this, "Tiger Palm", "target_if=min:debuff.mark_of_the_crane.remains,if=!prev_gcd.1.tiger_palm&!prev_gcd.1.energizing_elixir&energy=energy.max&chi<1&!buff.serenity.up" );
  serenity->add_action( "call_action_list,name=cd" );
  serenity->add_talent( this, "Rushing Jade Wind", "if=talent.rushing_jade_wind.enabled&!prev_gcd.1.rushing_jade_wind&buff.rushing_jade_wind.down",
                        "Needs to be rewritten for BFA" );
  serenity->add_talent( this, "Serenity", "if=cooldown.rising_sun_kick.remains<=2&cooldown.fists_of_fury.remains<=4" );
  serenity->add_action( this, "Fists of Fury", "if=prev_gcd.1.rising_sun_kick&prev_gcd.2.serenity" );
  serenity->add_action( this, "Fists of Fury", "if=buff.serenity.remains<=1.05" );
  serenity->add_action( this, "Rising Sun Kick", "target_if=min:debuff.mark_of_the_crane.remains" );
  serenity->add_talent( this, "Fist of the White Tiger", "if=prev_gcd.1.blackout_kick&prev_gcd.2.rising_sun_kick&chi.max-chi>2" );
  serenity->add_action( this, "Tiger Palm", "target_if=min:debuff.mark_of_the_crane.remains,if=prev_gcd.1.blackout_kick&prev_gcd.2.rising_sun_kick&chi.max-chi>1" );
  serenity->add_action( this, "Blackout Kick", "target_if=min:debuff.mark_of_the_crane.remains,if=!prev_gcd.1.blackout_kick&cooldown.rising_sun_kick.remains>=2&cooldown.fists_of_fury.remains>=2" );
  serenity->add_action( this, "Spinning Crane Kick", "if=active_enemies>=3&!prev_gcd.1.spinning_crane_kick" );
  serenity->add_action( this, "Rising Sun Kick", "target_if=min:debuff.mark_of_the_crane.remains");
  serenity->add_action( this, "Spinning Crane Kick", "if=!prev_gcd.1.spinning_crane_kick" );
  serenity->add_action( this, "Blackout Kick", "target_if=min:debuff.mark_of_the_crane.remains,if=!prev_gcd.1.blackout_kick" );

  // Serenity Opener
  serenity_openerSR -> add_talent( this, "Fist of the White Tiger", "if=buff.serenity.down" );
  serenity_openerSR -> add_action( this, "Tiger Palm", "target_if=min:debuff.mark_of_the_crane.remains,if=buff.serenity.down&chi<4" );
  serenity_openerSR -> add_action( "call_action_list,name=cd,if=buff.serenity.down" );
  serenity_openerSR -> add_action( "call_action_list,name=serenity,if=buff.bloodlust.down" );
  serenity_openerSR -> add_talent( this, "Serenity" );
  serenity_openerSR -> add_action( this, "Rising Sun Kick", "target_if=min:debuff.mark_of_the_crane.remains" );
  serenity_openerSR -> add_action( this, "Fists of Fury", "if=buff.serenity.remains<1" );
  serenity_openerSR -> add_action( this, "Blackout Kick", "target_if=min:debuff.mark_of_the_crane.remains,if=!prev_gcd.1.blackout_kick&cooldown.rising_sun_kick.remains>=2&cooldown.fists_of_fury.remains>=2" );
  serenity_openerSR -> add_action( this, "Blackout Kick", "target_if=min:debuff.mark_of_the_crane.remains" );

  // Multiple Targets
  aoe->add_action( "call_action_list,name=cd",
                   "Actions.AoE is intended for use with Hectic_Add_Cleave and currently needs to be optimized" );
  aoe->add_talent( this, "Energizing Elixir",
                   "if=!prev_gcd.1.tiger_palm&chi<=1&(cooldown.rising_sun_kick.remains=0|(talent.fist_of_the_white_tiger.enabled&cooldown.fist_of_the_white_tiger.remains=0)|energy<50)" );

  // Racials
  for ( size_t i = 0; i < racial_actions.size(); i++ )
  {
    if ( racial_actions[ i ] == "arcane_torrent" )
      aoe->add_action( racial_actions[ i ] + ",if=chi.max-chi>=1&energy.time_to_max>=0.5" );
  }

  aoe->add_action( this, "Fists of Fury", "if=talent.serenity.enabled&!equipped.drinking_horn_cover&cooldown.serenity.remains>=5&energy.time_to_max>2" );
  aoe->add_action( this, "Fists of Fury", "if=talent.serenity.enabled&equipped.drinking_horn_cover&(cooldown.serenity.remains>=15|cooldown.serenity.remains<=4)&energy.time_to_max>2" );
  aoe->add_action( this, "Fists of Fury", "if=!talent.serenity.enabled&energy.time_to_max>2" );
  aoe->add_action( this, "Fists of Fury", "if=cooldown.rising_sun_kick.remains>=3.5&chi<=5" );
  aoe->add_talent( this, "Whirling Dragon Punch" );
  aoe->add_action( this, "Rising Sun Kick", "target_if=min:debuff.mark_of_the_crane.remains,if=cooldown.whirling_dragon_punch.remains<gcd&!prev_gcd.1.rising_sun_kick&cooldown.fists_of_fury.remains>gcd" );
  aoe->add_talent( this, "Chi Burst", "if=chi<=3&(cooldown.rising_sun_kick.remains>=5|cooldown.whirling_dragon_punch.remains>=5)&energy.time_to_max>1" );
  aoe->add_talent( this, "Chi Burst" );
  aoe->add_action( this, "Spinning Crane Kick", "if=(active_enemies>=3|(buff.bok_proc.up&chi.max-chi>=0))&!prev_gcd.1.spinning_crane_kick&set_bonus.tier21_4pc" );
  aoe->add_action( this, "Spinning Crane Kick", "if=active_enemies>=3&!prev_gcd.1.spinning_crane_kick&cooldown.fists_of_fury.remains>gcd" );
  aoe->add_action( this, "Blackout Kick", "target_if=min:debuff.mark_of_the_crane.remains,if=!prev_gcd.1.blackout_kick&chi.max-chi>=1&set_bonus.tier21_4pc&(!set_bonus.tier19_2pc|talent.serenity.enabled)" );
  aoe->add_action( this, "Blackout Kick", "target_if=min:debuff.mark_of_the_crane.remains,if=(chi>1|buff.bok_proc.up|(talent.energizing_elixir.enabled&cooldown.energizing_elixir.remains<cooldown.fists_of_fury.remains))&((cooldown.rising_sun_kick.remains>1&(!talent.fist_of_the_white_tiger.enabled|cooldown.fist_of_the_white_tiger.remains>1)|chi>4)&(cooldown.fists_of_fury.remains>1|chi>2)|prev_gcd.1.tiger_palm)&!prev_gcd.1.blackout_kick" );
  aoe->add_action( this, "Crackling Jade Lightning", "if=equipped.the_emperors_capacitor&buff.the_emperors_capacitor.stack>=19&energy.time_to_max>3" );
  aoe->add_action( this, "Crackling Jade Lightning", "if=equipped.the_emperors_capacitor&buff.the_emperors_capacitor.stack>=14&cooldown.serenity.remains<13&talent.serenity.enabled&energy.time_to_max>3" );
  aoe->add_action( this, "Blackout Kick", "target_if=min:debuff.mark_of_the_crane.remains,if=!prev_gcd.1.blackout_kick&chi.max-chi>=1&set_bonus.tier21_4pc&buff.bok_proc.up" );
  aoe->add_action( this, "Tiger Palm", "target_if=min:debuff.mark_of_the_crane.remains,if=!prev_gcd.1.tiger_palm&!prev_gcd.1.energizing_elixir&(chi.max-chi>=2|energy.time_to_max<3)" );
  aoe->add_action( this, "Tiger Palm", "target_if=min:debuff.mark_of_the_crane.remains,if=!prev_gcd.1.tiger_palm&!prev_gcd.1.energizing_elixir&energy.time_to_max<=1&chi.max-chi>=2" );
  aoe->add_talent( this, "Chi Wave", "if=chi<=3&(cooldown.rising_sun_kick.remains>=5|cooldown.whirling_dragon_punch.remains>=5)&energy.time_to_max>1" );
  aoe->add_talent( this, "Chi Wave" );

  // Single Target
  st->add_talent( this, "Invoke Xuen, the White Tiger", "", "Default action list" );
  st->add_action( this, "Touch of Death" );
  st->add_action( this, "Storm, Earth, and Fire", "if=!buff.storm_earth_and_fire.up" );
  st->add_action( this, "Rising Sun Kick", "target_if=min:debuff.mark_of_the_crane.remains,if=azerite.swift_roundhouse.enabled&buff.swift_roundhouse.stack=2",
                  "Use Rising Sun Kick with 2 stacks of SR if applicable" );
  st->add_talent( this, "Rushing Jade Wind", "if=buff.rushing_jade_wind.down&!prev_gcd.1.rushing_jade_wind",
                  "Needs to be rewritten for BFA" );
  st->add_talent( this, "Energizing Elixir", "if=!prev_gcd.1.tiger_palm" );
  st->add_action( this, "Blackout Kick", "target_if=min:debuff.mark_of_the_crane.remains,if=!prev_gcd.1.blackout_kick&chi.max-chi>=1&set_bonus.tier21_4pc&buff.bok_proc.up",
                  "T21 set bonus conditional\n# Cast Blackout Kick if:\n# - Previous GCD was not Blackout Kick\n# - Blackout Kick! is available\n# - You're not at max Chi" );
  st->add_talent(this, "Fist of the White Tiger", "if=(chi<=2)", "Cast FotWT if you will gain 3 or more Chi");
  st->add_action( this, "Tiger Palm", "target_if=min:debuff.mark_of_the_crane.remains,if=chi<=3&energy.time_to_max<2",
                  "Cast Tiger Palm if:\n# - Previous GCD was not Tiger Palm\n# - Previous GCD was not EE (NOTE: redundant because of the Energy check, needs to be rewritten for BFA)\n# - You will cap Energy before next GCD\n# - You will gain 2 or more Chi" );
  st->add_action( this, "Tiger Palm", "target_if=min:debuff.mark_of_the_crane.remains,if=chi.max-chi>=2&buff.serenity.down&cooldown.fist_of_the_white_tiger.remains>energy.time_to_max" );
  st->add_talent( this, "Whirling Dragon Punch" );
  st->add_action( this, "Fists of Fury", "if=chi>=3&energy.time_to_max>2.5&azerite.swift_roundhouse.rank<3",
                  "FoF usage with Swift Roundhouse" );
  st->add_action( this, "Rising Sun Kick", "target_if=min:debuff.mark_of_the_crane.remains,if=((chi>=3&energy>=40)|chi>=5)&(talent.serenity.enabled|cooldown.serenity.remains>=6)&!azerite.swift_roundhouse.enabled",
                  "Cast Rising Sun Kick if:\n# - You are using SEF, and you have 3 or more Chi AND 40 or more energy OR 5 or more Chi\n# - You are using Serenity, 6 or more seconds remain on the cooldown of Serenity, and you have 3 or more Chi AND 40 or more energy OR 5 or more Chi " );
  st->add_action( this, "Fists of Fury", "if=!talent.serenity.enabled&(azerite.swift_roundhouse.rank<3|cooldown.whirling_dragon_punch.remains<13)",
                  "Cast Fists of Fury if:\n# - You are using SEF" );
  st->add_action( this, "Rising Sun Kick", "target_if=min:debuff.mark_of_the_crane.remains,if=cooldown.serenity.remains>=5|(!talent.serenity.enabled)&!azerite.swift_roundhouse.enabled",
                  "Cast RSK if:\n# - You are using SEF OR you are using Serenity and 5 or more seconds remain on the cooldown of Serenity" );
  st->add_action( this, "Blackout Kick", "target_if=min:debuff.mark_of_the_crane.remains,if=cooldown.fists_of_fury.remains>2&!prev_gcd.1.blackout_kick&energy.time_to_max>1&azerite.swift_roundhouse.rank>2",
                  "Cast Blackout Kick if:\n# - Previous GCD was not BoK\n# - You are not at max Chi" );
  st->add_action( this, "Flying Serpent Kick", "if=prev_gcd.1.blackout_kick&energy.time_to_max>2&chi>1,interrupt=1",
                  "Flying Serpent Kick for mastery resets" );
  st->add_action( this, "Blackout Kick", "target_if=min:debuff.mark_of_the_crane.remains,if=buff.swift_roundhouse.stack<2&!prev_gcd.1.blackout_kick" );
  st->add_action( this, "Crackling Jade Lightning", "if=equipped.the_emperors_capacitor&buff.the_emperors_capacitor.stack>=19&energy.time_to_max>3",
                  "Legacy for The Emperors Capacitor" );
  st->add_action( this, "Crackling Jade Lightning", "if=equipped.the_emperors_capacitor&buff.the_emperors_capacitor.stack>=14&cooldown.serenity.remains<13&talent.serenity.enabled&energy.time_to_max>3" );
  st->add_action( this, "Blackout Kick", "target_if=min:debuff.mark_of_the_crane.remains,if=!prev_gcd.1.blackout_kick" );
  st->add_talent( this, "Chi Wave" );
  st->add_talent( this, "Chi Burst", "if=energy.time_to_max>1&talent.serenity.enabled",
                  "Will need to be rewritten for BFA\n# Current rule: Cast Chi Burst if:\n# - You have 3 or less Chi\n# - RSK is up in 5 or more seconds OR WDP is up in 5 or more seconds\n# - You will not cap energy before the next GCD" );
  st->add_action( this, "Tiger Palm", "target_if=min:debuff.mark_of_the_crane.remains,if=!prev_gcd.1.tiger_palm&!prev_gcd.1.energizing_elixir&(chi.max-chi>=2|energy.time_to_max<3)&!buff.serenity.up",
                  "Cast Tiger Palm if:\n# - Previous ability was not Tiger Palm or Energizing Elixir\n# - You will gain at least 2 Chi, OR you will cap energy within 3 seconds (NOTE: Could cast TP even at 5 Chi just to prevent energy capping, in theory)" );
  st->add_talent( this, "Chi Burst", "if=chi.max-chi>=3&energy.time_to_max>1&!talent.serenity.enabled" );
}

// Mistweaver Combat Action Priority List ==================================

void monk_t::apl_combat_mistweaver()
{
  std::vector<std::string> racial_actions = get_racial_actions();
  action_priority_list_t* def             = get_action_priority_list( "default" );
  action_priority_list_t* st              = get_action_priority_list( "st" );
  action_priority_list_t* aoe             = get_action_priority_list( "aoe" );

  def->add_action( "auto_attack" );
  int num_items = (int)items.size();
  for ( int i = 0; i < num_items; i++ )
  {
    if ( items[ i ].has_special_effect( SPECIAL_EFFECT_SOURCE_NONE, SPECIAL_EFFECT_USE ) )
      def->add_action( "use_item,name=" + items[ i ].name_str );
  }
  for ( size_t i = 0; i < racial_actions.size(); i++ )
  {
    if ( racial_actions[ i ] == "arcane_torrent" )
      def->add_action( racial_actions[ i ] + ",if=chi.max-chi>=1&target.time_to_die<18" );
    else
      def->add_action( racial_actions[ i ] + ",if=target.time_to_die<18" );
  }

  def->add_action( "potion" );

  def->add_action( "run_action_list,name=aoe,if=active_enemies>=4" );
  def->add_action( "call_action_list,name=st,if=active_enemies<4" );

  st->add_action( this, "Rising Sun Kick" );
  st->add_action( this, "Blackout Kick",
                  "if=buff.teachings_of_the_monastery.stack=1&cooldown.rising_sun_kick.remains<12" );
  st->add_talent( this, "Chi Wave" );
  st->add_talent( this, "Chi Burst" );
  st->add_action( this, "Tiger Palm",
                  "if=buff.teachings_of_the_monastery.stack<3|buff.teachings_of_the_monastery.remains<2" );

  aoe->add_action( this, "Spinning Crane Kick" );
  aoe->add_talent( this, "Chi Wave" );
  aoe->add_talent( this, "Chi Burst" );
  //  aoe -> add_action( this, "Blackout Kick",
  //  "if=buff.teachings_of_the_monastery.stack=3&cooldown.rising_sun_kick.down" ); aoe -> add_action( this, "Tiger
  //  Palm", "if=buff.teachings_of_the_monastery.stack<3|buff.teachings_of_the_monastery.remains<2" );
}
