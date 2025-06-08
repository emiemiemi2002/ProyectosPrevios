-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Servidor: 127.0.0.1
-- Tiempo de generación: 01-12-2024 a las 22:53:57
-- Versión del servidor: 10.4.28-MariaDB
-- Versión de PHP: 8.2.4

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de datos: `caasa`
--

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `asesor`
--

CREATE TABLE `asesor` (
  `id_asesor` int(8) NOT NULL,
  `nomb_asesor` varchar(25) NOT NULL,
  `appat_asesor` varchar(15) NOT NULL,
  `apmat_asesor` varchar(15) NOT NULL,
  `tel_asesor` varchar(7) NOT NULL,
  `cel_asesor` varchar(12) NOT NULL,
  `email_asesor` varchar(35) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `automovil`
--

CREATE TABLE `automovil` (
  `nserie_auto` bigint(16) NOT NULL,
  `id_modelauto` int(8) NOT NULL,
  `id_color` int(5) NOT NULL,
  `precio_auto` decimal(9,2) NOT NULL,
  `estado_auto` varchar(15) NOT NULL,
  `disp_auto` varchar(15) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `cliente`
--

CREATE TABLE `cliente` (
  `id_client` bigint(11) NOT NULL,
  `nomb_client` varchar(25) NOT NULL,
  `appat_client` varchar(15) NOT NULL,
  `apmat_client` varchar(15) NOT NULL,
  `tel_client` varchar(7) NOT NULL,
  `cel_client` varchar(12) NOT NULL,
  `rfc_client` varchar(12) NOT NULL,
  `curp_client` varchar(18) NOT NULL,
  `fechnac_client` date NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `color`
--

CREATE TABLE `color` (
  `id_color` int(5) NOT NULL,
  `color` varchar(10) NOT NULL,
  `tono_color` varchar(15) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `compra`
--

CREATE TABLE `compra` (
  `id_compr` bigint(12) NOT NULL,
  `id_client` bigint(11) NOT NULL,
  `nserie_auto` bigint(16) NOT NULL,
  `id_asesor` int(8) NOT NULL,
  `id_formapago` int(5) NOT NULL,
  `id_planpago` int(5) NOT NULL,
  `fech_compr` date NOT NULL,
  `hora_compr` time NOT NULL,
  `monto_compr` decimal(9,2) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `contratacion`
--

CREATE TABLE `contratacion` (
  `id_contrat` bigint(12) NOT NULL,
  `id_client` bigint(11) NOT NULL,
  `nserie_auto` bigint(16) NOT NULL,
  `id_serv` bigint(11) NOT NULL,
  `id_formapago` int(5) NOT NULL,
  `id_planpago` int(5) NOT NULL,
  `fecha_contrat` date NOT NULL,
  `hora_contrat` time NOT NULL,
  `monto_contrat` decimal(7,2) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `domicilio`
--

CREATE TABLE `domicilio` (
  `id_client` bigint(11) NOT NULL,
  `ciudadmun_client` varchar(25) NOT NULL,
  `cp_client` varchar(5) NOT NULL,
  `colonia_client` varchar(25) NOT NULL,
  `calle_client` varchar(25) NOT NULL,
  `next_client` int(3) NOT NULL,
  `nint_client` int(2) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `forma_pago`
--

CREATE TABLE `forma_pago` (
  `id_formapago` int(5) NOT NULL,
  `forma_pago` varchar(25) NOT NULL,
  `tipo_pago` varchar(12) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `marca`
--

CREATE TABLE `marca` (
  `id_marca` int(5) NOT NULL,
  `marca` varchar(18) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `modelo`
--

CREATE TABLE `modelo` (
  `id_modelauto` int(8) NOT NULL,
  `id_marca` int(5) NOT NULL,
  `model_auto` varchar(25) NOT NULL,
  `año_auto` varchar(4) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `periodo_serv`
--

CREATE TABLE `periodo_serv` (
  `id_periodoserv` int(5) NOT NULL,
  `iteraciones_serv` int(2) NOT NULL,
  `tiempoentre_serv` varchar(15) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `plan_pago`
--

CREATE TABLE `plan_pago` (
  `id_planpago` int(5) NOT NULL,
  `plazo_pago` varchar(15) NOT NULL,
  `tasa_interes` decimal(3,2) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `servicio`
--

CREATE TABLE `servicio` (
  `id_serv` bigint(11) NOT NULL,
  `accion_serv` varchar(25) NOT NULL,
  `component_serv` varchar(20) NOT NULL,
  `precio_serv` decimal(7,2) NOT NULL,
  `disp_serv` varchar(15) NOT NULL,
  `id_tiposerv` int(5) NOT NULL,
  `id_periodoserv` int(5) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `tipo_serv`
--

CREATE TABLE `tipo_serv` (
  `id_tiposerv` int(5) NOT NULL,
  `tipo_serv` varchar(15) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Índices para tablas volcadas
--

--
-- Indices de la tabla `asesor`
--
ALTER TABLE `asesor`
  ADD PRIMARY KEY (`id_asesor`),
  ADD UNIQUE KEY `UNIQUE_EMAIL_ASESOR` (`email_asesor`);

--
-- Indices de la tabla `automovil`
--
ALTER TABLE `automovil`
  ADD PRIMARY KEY (`nserie_auto`),
  ADD KEY `FK_automovil_id_modelauto` (`id_modelauto`),
  ADD KEY `FK_automovil_id_color` (`id_color`);

--
-- Indices de la tabla `cliente`
--
ALTER TABLE `cliente`
  ADD PRIMARY KEY (`id_client`),
  ADD UNIQUE KEY `UNIQUE CURP` (`curp_client`),
  ADD UNIQUE KEY `UNIQUE RFC` (`rfc_client`);

--
-- Indices de la tabla `color`
--
ALTER TABLE `color`
  ADD PRIMARY KEY (`id_color`);

--
-- Indices de la tabla `compra`
--
ALTER TABLE `compra`
  ADD PRIMARY KEY (`id_compr`),
  ADD UNIQUE KEY `nserie_auto` (`nserie_auto`),
  ADD KEY `FK_compra_id_client` (`id_client`),
  ADD KEY `FK_compra_id_asesor` (`id_asesor`),
  ADD KEY `FK_compra_id_formapago` (`id_formapago`),
  ADD KEY `FK_compra_id_planpago` (`id_planpago`);

--
-- Indices de la tabla `contratacion`
--
ALTER TABLE `contratacion`
  ADD PRIMARY KEY (`id_contrat`),
  ADD KEY `FK_contratacion_id_client` (`id_client`),
  ADD KEY `FK_contratacion_nserie_auto` (`nserie_auto`),
  ADD KEY `FK_contratacion_id_serv` (`id_serv`),
  ADD KEY `FK_contratacion_id_formapago` (`id_formapago`),
  ADD KEY `FK_contratacion_id_planpago` (`id_planpago`);

--
-- Indices de la tabla `domicilio`
--
ALTER TABLE `domicilio`
  ADD PRIMARY KEY (`id_client`,`next_client`),
  ADD UNIQUE KEY `UNIQUE_ID_CLIENT` (`id_client`);

--
-- Indices de la tabla `forma_pago`
--
ALTER TABLE `forma_pago`
  ADD PRIMARY KEY (`id_formapago`),
  ADD UNIQUE KEY `forma_pago` (`forma_pago`);

--
-- Indices de la tabla `marca`
--
ALTER TABLE `marca`
  ADD PRIMARY KEY (`id_marca`),
  ADD UNIQUE KEY `marca` (`marca`);

--
-- Indices de la tabla `modelo`
--
ALTER TABLE `modelo`
  ADD PRIMARY KEY (`id_modelauto`),
  ADD UNIQUE KEY `model_auto` (`model_auto`),
  ADD KEY `FK_modelo_id_marca` (`id_marca`);

--
-- Indices de la tabla `periodo_serv`
--
ALTER TABLE `periodo_serv`
  ADD PRIMARY KEY (`id_periodoserv`),
  ADD UNIQUE KEY `tiempoentre_serv` (`tiempoentre_serv`);

--
-- Indices de la tabla `plan_pago`
--
ALTER TABLE `plan_pago`
  ADD PRIMARY KEY (`id_planpago`),
  ADD UNIQUE KEY `plazo_pago` (`plazo_pago`);

--
-- Indices de la tabla `servicio`
--
ALTER TABLE `servicio`
  ADD PRIMARY KEY (`id_serv`),
  ADD KEY `FK_servicio_id_tiposerv` (`id_tiposerv`),
  ADD KEY `FK_servicio_id_periodoserv` (`id_periodoserv`);

--
-- Indices de la tabla `tipo_serv`
--
ALTER TABLE `tipo_serv`
  ADD PRIMARY KEY (`id_tiposerv`),
  ADD UNIQUE KEY `tipo_serv` (`tipo_serv`);

--
-- Restricciones para tablas volcadas
--

--
-- Filtros para la tabla `automovil`
--
ALTER TABLE `automovil`
  ADD CONSTRAINT `FK_automovil_id_color` FOREIGN KEY (`id_color`) REFERENCES `color` (`id_color`),
  ADD CONSTRAINT `FK_automovil_id_modelauto` FOREIGN KEY (`id_modelauto`) REFERENCES `modelo` (`id_modelauto`);

--
-- Filtros para la tabla `compra`
--
ALTER TABLE `compra`
  ADD CONSTRAINT `FK_compra_id_asesor` FOREIGN KEY (`id_asesor`) REFERENCES `asesor` (`id_asesor`),
  ADD CONSTRAINT `FK_compra_id_client` FOREIGN KEY (`id_client`) REFERENCES `cliente` (`id_client`),
  ADD CONSTRAINT `FK_compra_id_formapago` FOREIGN KEY (`id_formapago`) REFERENCES `forma_pago` (`id_formapago`),
  ADD CONSTRAINT `FK_compra_id_planpago` FOREIGN KEY (`id_planpago`) REFERENCES `plan_pago` (`id_planpago`),
  ADD CONSTRAINT `FK_compra_nserie_auto` FOREIGN KEY (`nserie_auto`) REFERENCES `automovil` (`nserie_auto`);

--
-- Filtros para la tabla `contratacion`
--
ALTER TABLE `contratacion`
  ADD CONSTRAINT `FK_contratacion_id_client` FOREIGN KEY (`id_client`) REFERENCES `cliente` (`id_client`),
  ADD CONSTRAINT `FK_contratacion_id_formapago` FOREIGN KEY (`id_formapago`) REFERENCES `forma_pago` (`id_formapago`),
  ADD CONSTRAINT `FK_contratacion_id_planpago` FOREIGN KEY (`id_planpago`) REFERENCES `plan_pago` (`id_planpago`),
  ADD CONSTRAINT `FK_contratacion_id_serv` FOREIGN KEY (`id_serv`) REFERENCES `servicio` (`id_serv`),
  ADD CONSTRAINT `FK_contratacion_nserie_auto` FOREIGN KEY (`nserie_auto`) REFERENCES `automovil` (`nserie_auto`);

--
-- Filtros para la tabla `domicilio`
--
ALTER TABLE `domicilio`
  ADD CONSTRAINT `FK_domicilio_id_client` FOREIGN KEY (`id_client`) REFERENCES `cliente` (`id_client`);

--
-- Filtros para la tabla `modelo`
--
ALTER TABLE `modelo`
  ADD CONSTRAINT `FK_modelo_id_marca` FOREIGN KEY (`id_marca`) REFERENCES `marca` (`id_marca`);

--
-- Filtros para la tabla `servicio`
--
ALTER TABLE `servicio`
  ADD CONSTRAINT `FK_servicio_id_periodoserv` FOREIGN KEY (`id_periodoserv`) REFERENCES `periodo_serv` (`id_periodoserv`),
  ADD CONSTRAINT `FK_servicio_id_tiposerv` FOREIGN KEY (`id_tiposerv`) REFERENCES `tipo_serv` (`id_tiposerv`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
