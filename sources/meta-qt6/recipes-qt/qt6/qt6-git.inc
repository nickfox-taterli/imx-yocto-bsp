DESCRIPTION ?= "Qt is a cross-platform application development framework for desktop, embedded and mobile."
HOMEPAGE ?= "https://www.qt.io"

QT_MODULE ?= "${BPN}"
QT_MODULE_BRANCH ?= "6.2.2"
QT_MODULE_BRANCH_PARAM ?= "branch=${QT_MODULE_BRANCH}"

SRC_URI = "${QT_GIT}/${QT_GIT_PROJECT}/${QT_MODULE}.git;name=${QT_MODULE};${QT_MODULE_BRANCH_PARAM};protocol=${QT_GIT_PROTOCOL}"

CVE_PRODUCT = "qt"

S = "${WORKDIR}/git"

PV = "6.2.2"

SRCREV = "${SRCREV_${QT_MODULE}}"

SRCREV_tqtc-qmlcompilerplus = "e2da11130c5371aa8a5cb184fc4dc6fe3d0c85e1"
SRCREV_qt3d = "3291626751f71871cf7a152b00e1a41efc70087e"
SRCREV_qt3d-assimp = "5a38cd0a03015ceabbd5bc6efb0730dde1ef74e5"
SRCREV_qt5compat = "e91c93cb95303104a1fd38e9f5aacf8d69f5d0da"
SRCREV_qtbase = "eae95814a46386f8930eeae5486513a78a7a4ddc"
SRCREV_qtcharts = "e29fc5e0f5b5c83232cc55c8a6f58bcf01012793"
SRCREV_qtcoap = "edb38459c195e2d43c473afe65a6debb5719c948"
SRCREV_qtconnectivity = "a3e71fa606d0d9e2741fda322a05a61868802be3"
SRCREV_qtdatavis3d = "8e232b223fc6d384842fea02c37b54634597ab25"
SRCREV_qtdeclarative = "00c352c4d4b61f8c7a6243768bc5375c3dca3e76"
SRCREV_qtdeviceutilities = "df77ef89d3b1cbeda9996702e0a26a9a58c9f467"
SRCREV_qtimageformats = "c86d83c35ae13ec5e14df63a8d2d88215d34e1cd"
SRCREV_qtlottie = "2c73faa635069e4d62f0ec806602ef2aa148de5a"
SRCREV_qtmqtt = "8d02d69908e868193ec56f19d5d526c9d3b119d8"
SRCREV_qtmultimedia = "530831c141f4bdab2a737f4deff63e714e26af17"
SRCREV_qtnetworkauth = "b8ddff7689d0d7fb9d605e8fe3c4d80929745f94"
SRCREV_qtopcua = "f3b3fa1d18565da686b94e79ca73b315c5521632"
SRCREV_qtpositioning = "1294c29be50fa5cdf2d78afffac0451f7b4bc16a"
SRCREV_qtquick3d = "11237699336d41883ac6137e2021b59fc9c7244d"
SRCREV_qtquick3d-assimp = "5a38cd0a03015ceabbd5bc6efb0730dde1ef74e5"
SRCREV_qtquickdesigner-components = "e2a65b30c08b2614af09645d3e423b9e2255d644"
SRCREV_qtquicktimeline = "22f028d4fb74d540ad777aeb5e1afcd2e8d6bbe7"
SRCREV_qtremoteobjects = "60e52df675c4fada85c61f7c05a3f202e88c48d1"
SRCREV_qtscxml = "3db9cbf2ae81420307b56431d57365e790e113ce"
SRCREV_qtsensors = "5e0a3c037daad199d3fcdd976c25de119b22e6d1"
SRCREV_qtserialbus = "9687d42d9115544589e9e8733aaa548f26224e39"
SRCREV_qtserialport = "c94990da6fd9ab83bb57e2740961be1b1449c5e6"
SRCREV_qtshadertools = "1392cdf6d31e188dfe4e374bbd481a4a8fea68f8"
SRCREV_qtspeech = "462c3384467cec55a31fde11afb959321063a0ce"
SRCREV_qtsvg = "c858f65c04fa5b07f8b8ae539a48d4a89ceb9bac"
SRCREV_qttools = "f2d999c0fe298dcb3ffebbda9390e894f0e32d18"
SRCREV_qttools-qlitehtml = "4931b7aa30f256c20573d283561aa432fecf8f38"
SRCREV_qttools-qlitehtml-litehtml = "6236113734bb0a28467e5999e86fdd2834be8e01"
SRCREV_qttranslations = "a02924156981b4f7f40b47117b09985246ce03a4"
SRCREV_qtvirtualkeyboard = "07edaf2cb2db380f7030605a80842153098cbe51"
SRCREV_qtwayland = "e9ac64ab5e5364ae4d309227422588417463efdd"
SRCREV_qtwebchannel = "12a70972a3716433d2d454490a42b9c475337d2e"
SRCREV_qtwebengine = "432158aa0024fce9318df16b55604a9bc357fece"
SRCREV_qtwebengine-chromium = "39aa0ea99a30c9c15fb3640fe9a2638982548c0b"
SRCREV_qtwebsockets = "3de9f0eff79407939f37a3118b75125690407c0b"
SRCREV_qtwebview = "953f085e79dae4566fc641e4266e086890bd4aba"