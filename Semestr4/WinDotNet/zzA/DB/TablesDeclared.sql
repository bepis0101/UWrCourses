CREATE TABLE [dbo].[Student] (
	[ID] INT PRIMARY KEY NOT NULL,
	[Name] NVARCHAR(50) NOT NULL,
	[Surname] NVARCHAR(50) NOT NULL,
	[BirthDate] DATE NOT NULL
);
GO

CREATE TABLE [dbo].[Address] (
	[ID] INT PRIMARY KEY NOT NULL,
	[Street] NVARCHAR(50),
	[HouseNumber] NVARCHAR(10) NOT NULL,
	[FlatNumber] NVARCHAR(10),
	[ZipCode] NVARCHAR(50) NOT NULL,
	[CityID] INT FOREIGN KEY REFERENCES [dbo].[City]([ID]) NOT NULL
);
GO

CREATE TABLE [dbo].[City] (
	[ID] INT PRIMARY KEY NOT NULL,
	[Name] NVARCHAR(50) NOT NULL,
);
GO

CREATE TABLE [dbo].[StudentAddress] (
	[StudentID] INT FOREIGN KEY REFERENCES [dbo].[Student]([ID]) NOT NULL,
	[AddressID] INT FOREIGN KEY REFERENCES [dbo].[Address]([ID]) NOT NULL,
	PRIMARY KEY ([StudentID], [AddressID]),
);

GO

