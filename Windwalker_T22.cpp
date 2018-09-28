// Brewmaster Pre-Combat Action Priority List ============================

void monk_t::apl_pre_brewmaster()
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
  pre->add_talent( this, "Chi Burst", "if=(!talent.serenity.enabled|!talent.fist_of_the_white_tiger.enabled)" );
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
  action_priority_list_t* serenity          = get_action_priority_list( "serenity" );
  action_priority_list_t* aoe               = get_action_priority_list( "aoe" );
  action_priority_list_t* st                = get_action_priority_list( "st" );

  def->add_action( "auto_attack" );
  def->add_action( this, "Spear Hand Strike", "if=target.debuff.casting.react" );
  def->add_talent( this, "Rushing Jade Wind", "if=talent.serenity.enabled&cooldown.serenity.remains<3&energy.time_to_max>1&buff.rushing_jade_wind.down" );
  def->add_action( this, "Touch of Karma",
                   "interval=90,pct_health=0.5,if=!talent.good_karma.enabled,interval=90,pct_health=0.5",
                   "Touch of Karma on cooldown, if Good Karma is enabled equal to 100% of maximum health" );
  def->add_action( this, "Touch of Karma", "interval=90,pct_health=1,if=talent.good_karma.enabled,interval=90,pct_health=1" );

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

  def->add_action( "call_action_list,name=serenity,if=buff.serenity.up" );
  def->add_talent( this, "Fist of the White Tiger", "if=(energy.time_to_max<1|(talent.serenity.enabled&cooldown.serenity.remains<2))&chi.max-chi>=3" );
  def->add_action( this, "Tiger Palm", "target_if=min:debuff.mark_of_the_crane.remains,if=(energy.time_to_max<1|(talent.serenity.enabled&cooldown.serenity.remains<2))&chi.max-chi>=2&!prev_gcd.1.tiger_palm" );
  def->add_action( "call_action_list,name=cd" );
  def->add_action( "call_action_list,name=st,if=active_enemies<3",
                   "Call the ST action list if there are 2 or less enemies" );
  def->add_action( "call_action_list,name=aoe,if=active_enemies>=3",
                   "Call the AoE action list if there are 3 or more enemies" );

  // Cooldowns
  cd->add_talent( this, "Invoke Xuen, the White Tiger", "", "Cooldowns" );

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

  cd->add_action( this, "Touch of Death", "if=target.time_to_die>9" );
  cd->add_action( this, "Storm, Earth, and Fire", "if=cooldown.storm_earth_and_fire.charges=2|(cooldown.fists_of_fury.remains<=6&chi>=3&cooldown.rising_sun_kick.remains<=1)|target.time_to_die<=15" );
  cd->add_talent( this, "Serenity", "if=cooldown.rising_sun_kick.remains<=2|target.time_to_die<=12" );

  // Serenity
  serenity->add_action( this, "Rising Sun Kick", "target_if=min:debuff.mark_of_the_crane.remains,if=active_enemies<3|prev_gcd.1.spinning_crane_kick", "Serenity priority" );
  serenity->add_action( this, "Fists of Fury", "if=(buff.bloodlust.up&prev_gcd.1.rising_sun_kick&!azerite.swift_roundhouse.enabled)|buff.serenity.remains<1|(active_enemies>1&active_enemies<5)" );
  serenity->add_action( this, "Spinning Crane Kick", "if=!prev_gcd.1.spinning_crane_kick&(active_enemies>=3|(active_enemies=2&prev_gcd.1.blackout_kick))" );
  serenity->add_action( this, "Blackout Kick", "target_if=min:debuff.mark_of_the_crane.remains" );

  // Multiple Targets
  aoe->add_talent( this, "Whirling Dragon Punch", "",
                   "Actions.AoE is intended for use with Hectic_Add_Cleave and currently needs to be optimized" );
  aoe->add_talent( this, "Energizing Elixir", "if=!prev_gcd.1.tiger_palm&chi<=1&energy<50" );
  aoe->add_action( this, "Fists of Fury", "if=energy.time_to_max>3" );
  aoe->add_talent( this, "Rushing Jade Wind", "if=buff.rushing_jade_wind.down&energy.time_to_max>1" );
  aoe->add_action( this, "Rising Sun Kick", "target_if=min:debuff.mark_of_the_crane.remains,if=(talent.whirling_dragon_punch.enabled&cooldown.whirling_dragon_punch.remains<5)&cooldown.fists_of_fury.remains>3" );
  aoe->add_action( this, "Spinning Crane Kick", "if=!prev_gcd.1.spinning_crane_kick&(((chi>3|cooldown.fists_of_fury.remains>6)&(chi>=5|cooldown.fists_of_fury.remains>2))|energy.time_to_max<=3)" );
  aoe->add_talent( this, "Chi Burst", "if=chi<=3" );
  aoe->add_talent( this, "Fist of the White Tiger", "if=chi.max-chi>=3&(energy>46|buff.rushing_jade_wind.down)" );
  aoe->add_action( this, "Tiger Palm", "target_if=min:debuff.mark_of_the_crane.remains,if=chi.max-chi>=2&(energy>56|buff.rushing_jade_wind.down)&(!talent.hit_combo.enabled|!prev_gcd.1.tiger_palm)" );
  aoe->add_talent( this, "Chi Wave" );
  aoe->add_action( this, "Flying Serpent Kick", "if=buff.bok_proc.down,interrupt=1" );
  aoe->add_action( this, "Blackout Kick", "target_if=min:debuff.mark_of_the_crane.remains,if=!prev_gcd.1.blackout_kick&(buff.bok_proc.up|(talent.hit_combo.enabled&prev_gcd.1.tiger_palm&chi<4))" );

  // Single Target
  st->add_action( "cancel_buff,name=rushing_jade_wind,if=active_enemies=1&(!talent.serenity.enabled|cooldown.serenity.remains>3)", "Single target / Cleave priority");
  st->add_talent( this, "Whirling Dragon Punch" );
  st->add_action( this, "Rising Sun Kick", "target_if=min:debuff.mark_of_the_crane.remains,if=chi>=5" );
  st->add_action( this, "Fists of Fury", "if=energy.time_to_max>3" );
  st->add_action( this, "Rising Sun Kick", "target_if=min:debuff.mark_of_the_crane.remains" );
  st->add_talent( this, "Rushing Jade Wind", "if=buff.rushing_jade_wind.down&energy.time_to_max>1&active_enemies>1" );
  st->add_talent( this, "Fist of the White Tiger", "if=chi<=2&(buff.rushing_jade_wind.down|energy>46)" );
  st->add_talent( this, "Energizing Elixir", "if=chi<=3&energy<50" );
  st->add_action( this, "Blackout Kick", "target_if=min:debuff.mark_of_the_crane.remains,if=!prev_gcd.1.blackout_kick&(cooldown.rising_sun_kick.remains>3|chi>=3)&(cooldown.fists_of_fury.remains>4|chi>=4|(chi=2&prev_gcd.1.tiger_palm))&buff.swift_roundhouse.stack<2" );
  st->add_talent( this, "Chi Wave" );
  st->add_talent( this, "Chi Burst", "if=chi.max-chi>=1&active_enemies=1|chi.max-chi>=2" );
  st->add_action( this, "Tiger Palm", "target_if=min:debuff.mark_of_the_crane.remains,if=!prev_gcd.1.tiger_palm&chi.max-chi>=2&(buff.rushing_jade_wind.down|energy>56)" );
  st->add_action( this, "Flying Serpent Kick", "if=prev_gcd.1.blackout_kick&chi>3&buff.swift_roundhouse.stack<2,interrupt=1" );
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
