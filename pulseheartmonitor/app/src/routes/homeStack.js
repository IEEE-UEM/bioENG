import {createStackNavigator} from 'react-navigation-stack';
import {createAppContainer} from 'react-navigation';
import Inicio from '../pages/Home';
import Dados from '../pages/Info';
import Perfil from '../pages/Profile';

const screens = {
  Início: {
    screen: Inicio,
  },
  Dados: {
    screen: Dados,
  },
  Perfil: {
    screen: Perfil,
  },
};

const HomeStack = createStackNavigator(screens);

export default createAppContainer(HomeStack);
