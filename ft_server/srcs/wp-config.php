<?php
/**
 * The base configuration for WordPress
 *
 * The wp-config.php creation script uses this file during the
 * installation. You don't have to use the web site, you can
 * copy this file to "wp-config.php" and fill in the values.
 *
 * This file contains the following configurations:
 *
 * * MySQL settings
 * * Secret keys
 * * Database table prefix
 * * ABSPATH
 *
 * @link https://codex.wordpress.org/Editing_wp-config.php
 *
 * @package WordPress
 */

// ** MySQL settings - You can get this info from your web host ** //
/** The name of the database for WordPress */
define( 'DB_NAME', 'wordpress' );

/** MySQL database username */
define( 'DB_USER', 'hchorfi' );

/** MySQL database password */
define( 'DB_PASSWORD', 'password' );

/** MySQL hostname */
define( 'DB_HOST', 'localhost' );

/** Database Charset to use in creating database tables. */
define( 'DB_CHARSET', 'utf8mb4' );

/** The Database Collate type. Don't change this if in doubt. */
define( 'DB_COLLATE', '' );

/**#@+
 * Authentication Unique Keys and Salts.
 *
 * Change these to different unique phrases!
 * You can generate these using the {@link https://api.wordpress.org/secret-key/1.1/salt/ WordPress.org secret-key service}
 * You can change these at any point in time to invalidate all existing cookies. This will force all users to have to log in again.
 *
 * @since 2.6.0
 */
define( 'AUTH_KEY',         'U@lt*E?TsRs4Qr*0-?oDp]+oiddB[l?6|5@d=763Uz!MdQO[`S_F3q{SupUwD-]`' );
define( 'SECURE_AUTH_KEY',  'y)C/36Zlp-%eqTH-}Kk14#A:ORN<_Lg6:A97WszK65t-E:/]Q{(gXWN1yZn4|94e' );
define( 'LOGGED_IN_KEY',    'bP6.m]kK(dg{[uX,bY|-{63JcUbx>wRf9M+H9PefAM@l;OR};L6d0]K!3s[a71t0' );
define( 'NONCE_KEY',        'z,N{O#B)V5(b(Jf R=P*-pgpuhE!L/f4YZo`^khj uyG)ulvS>uscLp(eB(|5_ic' );
define( 'AUTH_SALT',        'VD$UW,xBx$yNoEJQ&pYc*MVRo6`^VM{eJd5d,me@:7Fj<H(4VQnVEPldu$>SQ`}^' );
define( 'SECURE_AUTH_SALT', 'qXX){I}r7!=v/bVa5`(nYY GM~@c4.V]%sri7~>xKa&U =!q@&|JsS_X<o t5vc1' );
define( 'LOGGED_IN_SALT',   '*T{1e~Id?IW;Wab(prcf(7o* .xd8GkkOITIDjXE?P+x&_X(CwkVC4K&C#}`|`}$' );
define( 'NONCE_SALT',       'v_KRz]TYu;X;}j1?_,AmfbRQ)K2X=(nLD+N3zC&=4~d6u;>B=w (M4ozbU+{387(' );

/**#@-*/

/**
 * WordPress Database Table prefix.
 *
 * You can have multiple installations in one database if you give each
 * a unique prefix. Only numbers, letters, and underscores please!
 */
$table_prefix = 'wp_';

/**
 * For developers: WordPress debugging mode.
 *
 * Change this to true to enable the display of notices during development.
 * It is strongly recommended that plugin and theme developers use WP_DEBUG
 * in their development environments.
 *
 * For information on other constants that can be used for debugging,
 * visit the Codex.
 *
 * @link https://codex.wordpress.org/Debugging_in_WordPress
 */
define( 'WP_DEBUG', false );

/* That's all, stop editing! Happy publishing. */

/** Absolute path to the WordPress directory. */
if ( ! defined( 'ABSPATH' ) ) {
	define( 'ABSPATH', dirname( __FILE__ ) . '/' );
}

/** Sets up WordPress vars and included files. */
require_once( ABSPATH . 'wp-settings.php' );
